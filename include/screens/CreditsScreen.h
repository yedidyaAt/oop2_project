#pragma once

#include "Screen.h"

#include <vector>
#include <memory>

// Scrolling credits (bottom -> top) on a black background, GTA-style. When the
// text finishes scrolling off the top, or the user clicks / presses Escape,
// it returns to the main menu.
class CreditsScreen : public Screen
{
public:
  // fromGameComplete: shown after finishing the last level (vs from the menu).
  CreditsScreen(sf::RenderWindow& window, bool fromGameComplete);

  void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
  void update(sf::Time dt) override;
  void draw(sf::RenderWindow& window) override;
  void onResize(sf::Vector2u newSize) override;

  ScreenAction action() const override;
  std::unique_ptr<Screen> takeNext() override;

private:
  void buildLines();
  void layout();

  sf::RenderWindow*      m_window;
  sf::RectangleShape     m_bg;
  std::vector<sf::Text>  m_lines;
  float                  m_scrollY = 0.f;   // current offset (grows as it scrolls up)
  float                  m_totalHeight = 0.f;
  bool                   m_fromGameComplete;
  ScreenAction           m_action = ScreenAction::None;
};
