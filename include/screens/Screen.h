#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

// What a screen asks the Game to do after each frame.
enum class ScreenAction
{
  None,     // keep running this screen
  Push,     // push m_next on top of this screen
  Replace,  // replace this screen with m_next
  Pop,      // remove this screen (return to the one below)
  Quit      // close the whole game
};

class Screen
{
public:
  virtual ~Screen() = default;

  virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;
  virtual void update(sf::Time dt) = 0;
  virtual void draw(sf::RenderWindow& window) = 0;

  // Called when the window is resized so screens can re-center their layout.
  virtual void onResize(sf::Vector2u /*newSize*/) {}

  // Called when this screen returns to the top of the stack (after a Pop above it).
  virtual void onResume() {}

  // Polled by Game after update(); tells Game what to do next.
  virtual ScreenAction action() const = 0;

  // The screen to push/replace with, valid when action() is Push/Replace.
  virtual std::unique_ptr<Screen> takeNext() = 0;
};
