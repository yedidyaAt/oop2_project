#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

#include "screens/Screen.h"

class Game
{
public:
  Game();
  void run();

private:
  void processEvents();
  void update(sf::Time dt);
  void render();
  void applyAction();

  void applyLetterboxView();   // keeps logical aspect ratio on any window size

  sf::RenderWindow                    m_window;
  std::stack<std::unique_ptr<Screen>> m_screens;
};
