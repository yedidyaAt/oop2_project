#pragma once

#include <SFML/Graphics.hpp>

#include "Car.h"

class Game
{
public:
  Game();

  void run();

  template <typename T>
  void handle(T&)const{}
  void handle(sf::Event::Closed& closed);
private:
  sf::RenderWindow m_window;
  sf::Clock        m_clock;
  float            m_timeLeft;
  int              m_frameCount;
  float           m_timeAccumulated;
};