#include "MenuScreen.h"
#include "LevelSelectScreen.h"
#include "HelpScreen.h"
#include "CreditsScreen.h"

#include "ResourceManager.h"
#include "Fonts.h"
#include "UISettings.h"
#include "DisplaySettings.h"
#include "SoundManager.h"
#include "Sounds.h"
#include "Musics.h"

namespace {
  constexpr float LOGICAL_W = static_cast<float>(display::WINDOW_WIDTH);
  constexpr float LOGICAL_H = static_cast<float>(display::WINDOW_HEIGHT);
}

MenuScreen::MenuScreen(sf::RenderWindow& window, std::vector<std::string> playlist) :
  m_window(window),
  m_playlist(std::move(playlist)),
  m_bg(UITextures::MENU_BG),
  m_title(ResourceManager::getInstance().getFont(fonts::MAIN))
{
  SoundManager::getInstance().playMusic(musics::OPENING);

  m_title.setString("EXTREME CAR PARKING");
  m_title.setCharacterSize(ui::TITLE_SIZE);
  m_title.setFillColor(ui::TITLE_COL);
  m_title.setOutlineColor(ui::OUTLINE_COL);
  m_title.setOutlineThickness(ui::TITLE_OUTLINE);

  for (const auto& label : { "Levels", "Help", "Credits", "Quit" })
    m_buttons.push_back(std::make_unique<Button>(label,
      sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ ui::BTN_WIDTH, ui::BTN_HEIGHT }));

  layout();
}

void MenuScreen::layout()
{
  m_bg.fitTo({ LOGICAL_W, LOGICAL_H });

  auto b = m_title.getLocalBounds();
  m_title.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
  m_title.setPosition({ LOGICAL_W / 2.f, 110.f });

  // stack buttons centered
  const std::size_t n = m_buttons.size();
  const float stackH = n * ui::BTN_HEIGHT + (n - 1) * ui::BTN_SPACING;
  float y = (LOGICAL_H / 2.f) - stackH / 2.f + ui::BTN_HEIGHT / 2.f + 40.f;

  for (auto& btn : m_buttons)
  {
    btn->setCenter({ LOGICAL_W / 2.f, y });
    y += ui::BTN_HEIGHT + ui::BTN_SPACING;
  }
}

void MenuScreen::onResize(sf::Vector2u /*newSize*/)
{
  layout();
}

void MenuScreen::onResume()
{
  SoundManager::getInstance().playMusic(musics::OPENING);
}

void MenuScreen::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
  if (event.is<sf::Event::Closed>())
  {
    m_action = ScreenAction::Quit;
    return;
  }

  const sf::Vector2f mouse =
    window.mapPixelToCoords(sf::Mouse::getPosition(window));

  if (const auto* moved = event.getIf<sf::Event::MouseMoved>())
  {
    (void)moved;
    for (auto& btn : m_buttons)
      btn->updateHover(mouse);
  }

  if (const auto* mb = event.getIf<sf::Event::MouseButtonPressed>())
  {
    if (mb->button == sf::Mouse::Button::Left)
    {
      for (std::size_t i = 0; i < m_buttons.size(); ++i)
      {
        if (!m_buttons[i]->contains(mouse))
          continue;

        SoundManager::getInstance().playEffectSound(sounds::CLICKING_BUTTON);

        switch (i)
        {
        case 0: // Levels
          m_next = std::make_unique<LevelSelectScreen>(m_window, m_playlist);
          m_action = ScreenAction::Push;
          break;
        case 1: // Help
          m_next = std::make_unique<HelpScreen>(m_window);
          m_action = ScreenAction::Push;
          break;
        case 2: // Credits
          m_next = std::make_unique<CreditsScreen>(m_window, false);
          m_action = ScreenAction::Push;
          break;
        case 3: // Quit
          m_action = ScreenAction::Quit;
          break;
        default: break;
        }
        return;
      }
    }
  }
}

void MenuScreen::update(sf::Time /*dt*/) {}

void MenuScreen::draw(sf::RenderWindow& window)
{
  window.draw(m_bg);
  window.draw(m_title);
  for (const auto& btn : m_buttons)
    window.draw(*btn);
}

ScreenAction MenuScreen::action() const {
  return m_action;
}

std::unique_ptr<Screen> MenuScreen::takeNext()
{
  return std::move(m_next);
}
