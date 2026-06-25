#include "LevelSelectScreen.h"
#include "GameScreen.h"

#include "ResourceManager.h"
#include "Fonts.h"
#include "UISettings.h"
#include "DisplaySettings.h"
#include "SoundManager.h"
#include "Sounds.h"
#include "Progress.h"

namespace {
  constexpr float LOGICAL_W = static_cast<float>(display::WINDOW_WIDTH);
  constexpr float LOGICAL_H = static_cast<float>(display::WINDOW_HEIGHT);
}

LevelSelectScreen::LevelSelectScreen(sf::RenderWindow& window, std::vector<std::string> playlist) :
  m_window(window),
  m_playlist(std::move(playlist)),
  m_bg(UITextures::LEVELS_BG),
  m_title(ResourceManager::getInstance().getFont(Fonts::MAIN))
{
  m_title.setString("SELECT LEVEL");
  m_title.setCharacterSize(ui::HEADING_SIZE);
  m_title.setFillColor(ui::TITLE_COL);
  m_title.setOutlineColor(ui::OUTLINE_COL);
  m_title.setOutlineThickness(ui::TITLE_OUTLINE);

  m_back  = std::make_unique<Button>("Back",
    sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ 200.f, ui::BTN_HEIGHT });
  m_reset = std::make_unique<Button>("Reset Progress",
    sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ 240.f, ui::BTN_HEIGHT });

  build();
  layout();
}

void LevelSelectScreen::build()
{
  m_tiles.clear();
  const std::size_t count = m_playlist.size();
  for (std::size_t i = 0; i < count; ++i)
  {
    bool unlocked = Progress::getInstance().isUnlocked(i);
    m_tiles.push_back(std::make_unique<LevelTile>(i + 1, unlocked,
      sf::Vector2f{ 0.f, 0.f }));
  }
}

void LevelSelectScreen::layout()
{
  m_bg.fitTo({ LOGICAL_W, LOGICAL_H });

  {
    auto b = m_title.getLocalBounds();
    m_title.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
    m_title.setPosition({ LOGICAL_W / 2.f, 56.f });
  }

  const int cols = ui::GRID_COLS;
  const int n    = static_cast<int>(m_tiles.size());
  const int rows = (n + cols - 1) / cols;
  const float step = ui::TILE_SIZE + ui::TILE_GAP;

  const float gridW = cols * ui::TILE_SIZE + (cols - 1) * ui::TILE_GAP;
  const float gridH = rows * ui::TILE_SIZE + (rows - 1) * ui::TILE_GAP;
  const float startX = LOGICAL_W / 2.f - gridW / 2.f + ui::TILE_SIZE / 2.f;
  const float startY = 110.f + ui::TILE_SIZE / 2.f;
  (void)gridH;

  for (int i = 0; i < n; ++i)
  {
    const int r = i / cols;
    const int c = i % cols;
    sf::Vector2f center{ startX + c * step, startY + r * step };
    // rebuild tile at new position (tiles cache their layout in ctor)
    bool unlocked = m_tiles[static_cast<std::size_t>(i)]->isUnlocked();
    m_tiles[static_cast<std::size_t>(i)] =
      std::make_unique<LevelTile>(static_cast<std::size_t>(i + 1), unlocked, center);
  }

  m_back->setCenter({ LOGICAL_W / 2.f - 140.f, LOGICAL_H - 48.f });
  m_reset->setCenter({ LOGICAL_W / 2.f + 150.f, LOGICAL_H - 48.f });
}

void LevelSelectScreen::onResize(sf::Vector2u /*newSize*/) { layout(); }

void LevelSelectScreen::onResume()
{
  SoundManager::getInstance().playMusic(Musics::OPENING);
  build();    // re-read Progress (locks may have changed)
  layout();   // re-position the freshly-built tiles
}

void LevelSelectScreen::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
  if (event.is<sf::Event::Closed>())
  {
    m_action = ScreenAction::Quit;
    return;
  }

  const sf::Vector2f mouse =
    window.mapPixelToCoords(sf::Mouse::getPosition(window));

  if (event.getIf<sf::Event::MouseMoved>())
  {
    for (auto& t : m_tiles)
    {
      t->updateHover(mouse);
    }
    m_back->updateHover(mouse);
    m_reset->updateHover(mouse);
  }

  if (const auto* mb = event.getIf<sf::Event::MouseButtonPressed>())
  {
    if (mb->button != sf::Mouse::Button::Left)
      return;

    if (m_back->contains(mouse))
    {
      SoundManager::getInstance().playEffectSound(Sounds::CLICKING_BUTTON);
      m_action = ScreenAction::Pop;
      return;
    }

    if (m_reset->contains(mouse))
    {
      SoundManager::getInstance().playEffectSound(Sounds::CLICKING_BUTTON);
      Progress::getInstance().resetAll();
      build();
      layout();
      return;
    }

    for (std::size_t i = 0; i < m_tiles.size(); ++i)
    {
      if (m_tiles[i]->contains(mouse) && m_tiles[i]->isUnlocked())
      {
        SoundManager::getInstance().playEffectSound(Sounds::CLICKING_BUTTON);
        m_next = std::make_unique<GameScreen>(m_window, m_playlist, i);
        m_action = ScreenAction::Push;
        return;
      }
    }
  }

  if (const auto* key = event.getIf<sf::Event::KeyPressed>())
    if (key->code == sf::Keyboard::Key::Escape)
      m_action = ScreenAction::Pop;
}

void LevelSelectScreen::update(sf::Time /*dt*/) {}

void LevelSelectScreen::draw(sf::RenderWindow& window)
{
  window.draw(m_bg);
  window.draw(m_title);
  for (const auto& t : m_tiles)
    window.draw(*t);
  window.draw(*m_back);
  window.draw(*m_reset);
}

ScreenAction LevelSelectScreen::action() const { return m_action; }
std::unique_ptr<Screen> LevelSelectScreen::takeNext() { return std::move(m_next); }
