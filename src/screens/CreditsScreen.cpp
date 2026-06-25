#include "CreditsScreen.h"

#include "ResourceManager.h"
#include "Fonts.h"
#include "UISettings.h"
#include "DisplaySettings.h"

#include "Musics.h"
#include "SoundManager.h"

namespace {
  constexpr float LOGICAL_W = static_cast<float>(display::WINDOW_WIDTH);
  constexpr float LOGICAL_H = static_cast<float>(display::WINDOW_HEIGHT);

  // Each entry: {text, characterSize}. Empty text = spacer line.
  struct Line { const char* text; unsigned size; };

  const std::vector<Line> CREDIT_LINES = {
    {"EXTREME CAR PARKING", ui::TITLE_SIZE},
    {"A Physics-Based Parking Challenge", ui::BODY_SIZE},
    {"", ui::BODY_SIZE},
    {"", ui::BODY_SIZE},
    {"Game Design & Programming", ui::SMALL_SIZE},
    {"Yedidya Atlan", ui::HEADING_SIZE},
    {"", ui::SMALL_SIZE},
    {"Game Design & Programming", ui::SMALL_SIZE},
    {"Elisha Tzarlin", ui::HEADING_SIZE},
    {"", ui::BODY_SIZE},
    {"", ui::BODY_SIZE},
    {"Course Instructor", ui::SMALL_SIZE},
    {"Matan perrel", ui::HEADING_SIZE},
    {"", ui::SMALL_SIZE},
    {"Teaching Mentor", ui::SMALL_SIZE},
    {"Zvi Melamed", ui::HEADING_SIZE},
    {"", ui::BODY_SIZE},
    {"", ui::BODY_SIZE},
    {"Built With", ui::SMALL_SIZE},
    {"C++ & SFML 3.0", ui::BODY_SIZE},
    {"", ui::BODY_SIZE},
    {"", ui::BODY_SIZE},
    {"Thanks for playing!", ui::HEADING_SIZE},
  };
}

CreditsScreen::CreditsScreen(sf::RenderWindow& window, bool fromGameComplete) :
  m_window(&window),
  m_fromGameComplete(fromGameComplete)
{
  m_bg.setFillColor(sf::Color::Black);
  buildLines();
  layout();

  SoundManager::getInstance().playMusic(Musics::CREDITS, true);   // force restart
}

void CreditsScreen::buildLines()
{
  m_lines.clear();
  for (const auto& l : CREDIT_LINES)
  {
    sf::Text t(ResourceManager::getInstance().getFont(Fonts::MAIN));
    t.setString(l.text);
    t.setCharacterSize(l.size);
    t.setFillColor(ui::TITLE_COL);
    if (l.size >= ui::HEADING_SIZE)
    {
      t.setOutlineColor(ui::OUTLINE_COL);
      t.setOutlineThickness(2.f);
    }
    else
    {
      t.setFillColor(ui::DIM_COL);
    }
    m_lines.push_back(t);
  }
}

void CreditsScreen::layout()
{
  m_bg.setSize({ LOGICAL_W, LOGICAL_H });
  m_bg.setPosition({ 0.f, 0.f });

  // stack lines vertically, measuring total height; start below the screen
  float y = 0.f;
  for (auto& t : m_lines)
  {
    auto b = t.getLocalBounds();
    t.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y });
    t.setPosition({ LOGICAL_W / 2.f, y });
    y += t.getCharacterSize() + ui::CREDITS_LINE_GAP;
  }
  m_totalHeight = y;
  m_scrollY = 0.f;
}

void CreditsScreen::onResize(sf::Vector2u /*newSize*/) { layout(); }

void CreditsScreen::handleEvent(const sf::Event& event, const sf::RenderWindow& /*window*/)
{
  if (event.is<sf::Event::Closed>())
  {
    m_action = ScreenAction::Quit;
    return;
  }

  if (event.getIf<sf::Event::MouseButtonPressed>())
    m_action = ScreenAction::Pop;

  if (const auto* key = event.getIf<sf::Event::KeyPressed>())
    if (key->code == sf::Keyboard::Key::Escape || key->code == sf::Keyboard::Key::Enter)
      m_action = ScreenAction::Pop;
}

void CreditsScreen::update(sf::Time dt)
{
  m_scrollY += ui::CREDITS_SCROLL_SPEED * dt.asSeconds();

  // when everything has scrolled past the top, return to menu
  if (m_scrollY > m_totalHeight + LOGICAL_H)
    m_action = ScreenAction::Pop;
}

void CreditsScreen::draw(sf::RenderWindow& window)
{
  window.draw(m_bg);

  // lines begin just below the bottom edge and rise as m_scrollY grows
  const float baseY = LOGICAL_H - m_scrollY;
  for (auto& t : m_lines)
  {
    sf::Text line = t;
    line.move({ 0.f, baseY });
    window.draw(line);
  }
}

ScreenAction CreditsScreen::action() const { return m_action; }
std::unique_ptr<Screen> CreditsScreen::takeNext() { return nullptr; }
