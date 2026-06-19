#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GameObject.h"
#include "ControlStrategy.h"

class Car:public sf::Transformable,public GameObject
{
public:
  Car(const sf::Texture& texture, const sf::Vector2f& pos,
                  float fitSize,
                  sf::Angle angle,
                  std::unique_ptr<ControlStrategy> control);

    
  void draw(sf::RenderTarget& window, sf::RenderStates state)const override;

  void update(sf::Time time);  
  sf::FloatRect getGlobalBounds() const;
  std::array<sf::Vector2f, 4> getCorners() const override;

private:
  void drive(float time);
  void gas(float time);
  void reverse(float time);
  void rotateWheels();
  void brakes(float time);

  void rotateRight(float time);
  void rotateLeft(float time);
  void centerWheel(float time);
  void gravitySlow(float time);
  void slowEngine(float time, float slowBy);

  std::unique_ptr<ControlStrategy> m_control;
  sf::Sprite m_whileR;
  sf::Sprite m_whileL;
  float              m_angleWheel;
  float              m_heading;
  float              m_speed;
};
