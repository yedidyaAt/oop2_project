#pragma once

#include <SFML/Graphics.hpp>

#include "Loader.h"
#include "GameObject.h"

#include <memory>

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

  Loader m_loader;
  std::vector<std::unique_ptr<GameObject>> m_objects = std::vector<std::unique_ptr<GameObject>>();
};