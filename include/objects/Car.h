#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "ControlStrategy.h"

class Car:public sf::Transformable,public sf::Drawable
{
public:
  Car(std::unique_ptr<ControlStrategy> control);
    
  void draw(sf::RenderTarget& window, sf::RenderStates state)const override;

  void update(float time);

  void drive(float time);
  void gas(float time);
  void reverse(float time);
  void rotateWheels();
  void brakes(float time);

  void rotateRight(float time);
  void rotateLeft(float time);
  void gravitySlow(float time);
  void slowEngine(float time, float slowBy);
  
private:
  void centerWheel(float time);

  std::unique_ptr<ControlStrategy> m_control;
  sf::RectangleShape m_rCar;
  sf::RectangleShape m_whileR;
  sf::RectangleShape m_whileL;
  float              m_angleWheel;
  float              m_heading;
  float              m_speed;
};
