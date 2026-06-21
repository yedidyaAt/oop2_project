#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "GameObject.h"
#include "LevelData.h"


class LevelManager
{
public:
  LevelManager(sf::RenderWindow& window,LevelData levelData);

  void run();

private:
  void update(sf::Time time);
  void checkConflict();
  void draw();


  template <typename T>
  void handle(T&)const {}
  void handle(sf::Event::Closed& closed);



  sf::RenderWindow&                        m_window;
  std::unique_ptr<GameObject>              m_car       = std::unique_ptr<GameObject>();
  std::vector<std::unique_ptr<GameObject>> m_blocksObj = std::vector<std::unique_ptr<GameObject>>();
  std::vector<std::unique_ptr<GameObject>> m_decalsObj = std::vector<std::unique_ptr<GameObject>>();
};