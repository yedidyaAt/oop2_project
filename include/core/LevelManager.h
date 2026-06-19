#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "GameObject.h"


class LevelManager
{
public:
  LevelManager(sf::RenderWindow& window, std::vector<std::unique_ptr<GameObject>> objects, std::unique_ptr<GameObject> car);

  void run();

private:
  void update(sf::Time time);
  void checkConflict();
  void draw();


  template <typename T>
  void handle(T&)const {}
  void handle(sf::Event::Closed& closed);






  sf::RenderWindow&                        m_window;
  std::vector<std::unique_ptr<GameObject>> m_objects;
  std::unique_ptr<GameObject>              m_car;
};