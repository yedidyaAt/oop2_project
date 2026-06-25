#include "HelpScreen.h"

#include "ResourceManager.h"
#include "Fonts.h"
#include "UISettings.h"
#include "DisplaySettings.h"
#include "SoundManager.h"
#include "Sounds.h"

namespace {
  constexpr float LOGICAL_W = static_cast<float>(display::WINDOW_WIDTH);
  constexpr float LOGICAL_H = static_cast<float>(display::WINDOW_HEIGHT);

  const std::string HELP_TEXT =
    "Goal:\n"
    "Drive your car into the highlighted parking spot and stop there,\n"
    "lined up with the correct angle.\n"
    "\n"
    "Controls:\n"
    "   Up Arrow      -  accelerate forward\n"
    "   Down Arrow    -  reverse\n"
    "   Left / Right  -  steer the front wheels\n"
    "   Space         -  brake\n"
    "\n"
    "Rules:\n"
    "   - Touching any wall, car or obstacle fails the level.\n"
    "   - You must come to a full stop inside the spot to win.\n"
    "   - The faster you park, the more stars you earn.\n"
    "\n"
    "Tip: ease off the gas early and let the car roll into place.";
}

HelpScreen::HelpScreen(sf::RenderWindow& window) :
  m_window(window),
  m_bg(UITextures::MENU_BG),
  m_title(ResourceManager::getInstance().getFont(Fonts::MAIN)),
  m_body(ResourceManager::getInstance().getFont(Fonts::MAIN))
{
  m_title.setString("HOW TO PLAY");
  m_title.setCharacterSize(ui::HEADING_SIZE);
  m_title.setFillColor(ui::TITLE_COL);
  m_title.setOutlineColor(ui::OUTLINE_COL);
  m_title.setOutlineThickness(ui::TITLE_OUTLINE);

  m_body.setString(HELP_TEXT);
  m_body.setCharacterSize(ui::BODY_SIZE);
  m_body.setFillColor(ui::BODY_COL);
  m_body.setOutlineColor(ui::OUTLINE_COL);
  m_body.setOutlineThickness(1.f);
  m_body.setLineSpacing(1.15f);

  m_back = std::make_unique<Button>("Back",
    sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ ui::BTN_WIDTH, ui::BTN_HEIGHT });

  m_dim.setSize({ static_cast<float>(display::WINDOW_WIDTH),
                static_cast<float>(display::WINDOW_HEIGHT) });
  m_dim.setPosition({ 0.f, 0.f });
  m_dim.setFillColor(ui::MODAL_DIM);

  layout();
}

void HelpScreen::layout()
{
  m_bg.fitTo({ LOGICAL_W, LOGICAL_H });

  {
    auto b = m_title.getLocalBounds();
    m_title.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
    m_title.setPosition({ LOGICAL_W / 2.f, 60.f });
  }

  // left-aligned body, roughly centered as a block
  {
    auto b = m_body.getLocalBounds();
    m_body.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y });
    m_body.setPosition({ LOGICAL_W / 2.f, 110.f });
  }

  m_back->setCenter({ LOGICAL_W / 2.f, LOGICAL_H - 50.f });
}

void HelpScreen::onResize(sf::Vector2u /*newSize*/) { layout(); }

void HelpScreen::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
  if (event.is<sf::Event::Closed>())
  {
    m_action = ScreenAction::Quit;
    return;
  }

  const sf::Vector2f mouse =
    window.mapPixelToCoords(sf::Mouse::getPosition(window));

  if (event.getIf<sf::Event::MouseMoved>())
    m_back->updateHover(mouse);

  if (const auto* mb = event.getIf<sf::Event::MouseButtonPressed>())
  {
    if (mb->button == sf::Mouse::Button::Left && m_back->contains(mouse))
    {
      SoundManager::getInstance().playEffectSound(Sounds::CLICKING_BUTTON);
      m_action = ScreenAction::Pop;
    }
  }

  if (const auto* key = event.getIf<sf::Event::KeyPressed>())
    if (key->code == sf::Keyboard::Key::Escape)
      m_action = ScreenAction::Pop;
}

void HelpScreen::update(sf::Time /*dt*/) {}

void HelpScreen::draw(sf::RenderWindow& window)
{
  window.draw(m_bg);
  window.draw(m_dim);
  window.draw(m_title);
  window.draw(m_body);
  window.draw(*m_back);
}

ScreenAction HelpScreen::action() const { return m_action; }
std::unique_ptr<Screen> HelpScreen::takeNext() { return nullptr; }
