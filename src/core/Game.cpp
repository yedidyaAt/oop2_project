#include "core/Game.h"

#include "screens/MenuScreen.h"
#include "ui/ViewUtils.h"
#include "data/loader/Playlist.h"
#include "Progress.h"
#include "DisplaySettings.h"

#include <stdexcept>

namespace {
  constexpr float LOGICAL_W = static_cast<float>(display::WINDOW_WIDTH);
  constexpr float LOGICAL_H = static_cast<float>(display::WINDOW_HEIGHT);
}

Game::Game() :
  m_window(sf::VideoMode(sf::Vector2u{ display::WINDOW_WIDTH, display::WINDOW_HEIGHT }),
           "Extreme Car Parking",
           sf::Style::Default)
{
  m_window.setFramerateLimit(60);

  Playlist playlist;
  auto levels = playlist.getPlaylist("resources/levels/levels.json");
  for (auto& name : levels)
    name = "resources/levels/" + name;

  Progress::getInstance().init(levels.size());

  m_screens.push(std::make_unique<MenuScreen>(m_window, std::move(levels)));
}

void Game::applyLetterboxView()
{
  sf::View view({ LOGICAL_W / 2.f, LOGICAL_H / 2.f }, { LOGICAL_W, LOGICAL_H });
  view.setViewport(viewUtils::letterboxViewport(LOGICAL_W, LOGICAL_H, m_window.getSize()));
  m_window.setView(view);
}

void Game::run()
{
  sf::Clock clock;

  while (m_window.isOpen() && !m_screens.empty())
  {
    sf::Time dt = clock.restart();

    processEvents();
    if (m_screens.empty() || !m_window.isOpen()) 
      break;

    update(dt);
    if (m_screens.empty() || !m_window.isOpen()) 
      break;

    render();
  }
}

void Game::processEvents()
{
  while (const auto event = m_window.pollEvent())
  {
    if (event->is<sf::Event::Closed>())
    {
      m_window.close();
      return;
    }

    if (const auto* resized = event->getIf<sf::Event::Resized>())
    {
      applyLetterboxView();
      if (!m_screens.empty())
        m_screens.top()->onResize(resized->size);
    }

    if (!m_screens.empty())
      m_screens.top()->handleEvent(*event, m_window);
  }
}

void Game::update(sf::Time dt)
{
  if (m_screens.empty())
    return;

  m_screens.top()->update(dt);
  applyAction();
}

void Game::applyAction()
{
  if (m_screens.empty())
    return;

  Screen& top = *m_screens.top();

  switch (top.action())
  {
  case ScreenAction::None:
    break;
  case ScreenAction::Push:
  {
    auto next = top.takeNext();
    if (next) 
      m_screens.push(std::move(next));
    break;
  }
  case ScreenAction::Replace:
  {
    auto next = top.takeNext();
    m_screens.pop();
    if (next) m_screens.push(std::move(next));
    break;
  }
  case ScreenAction::Pop:
    m_screens.pop();
    if (!m_screens.empty())
      m_screens.top()->onResume();   // notify the screen now revealed
    break;
  case ScreenAction::Quit:
    m_window.close();
    while (!m_screens.empty())
      m_screens.pop();
    break;
  }
}

void Game::render()
{
  applyLetterboxView();

  m_window.clear(sf::Color({ 160, 160, 165 }));
  

  if (!m_screens.empty())
    m_screens.top()->draw(m_window);

  m_window.display();
}
