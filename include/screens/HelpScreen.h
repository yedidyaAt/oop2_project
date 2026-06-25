#pragma once

#include "Screen.h"
#include "ui/Button.h"
#include "ui/Background.h"

#include <memory>

class HelpScreen : public Screen
{
public:
  explicit HelpScreen(sf::RenderWindow& window);

  void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
  void update(sf::Time dt) override;
  void draw(sf::RenderWindow& window) override;
  void onResize(sf::Vector2u newSize) override;

  ScreenAction action() const override;
  std::unique_ptr<Screen> takeNext() override;

private:
  void layout();

  sf::RenderWindow&       m_window;
  Background              m_bg;
  sf::Text                m_title;
  sf::Text                m_body;
  std::unique_ptr<Button> m_back;
  ScreenAction            m_action = ScreenAction::None;
  sf::RectangleShape m_dim;
};
