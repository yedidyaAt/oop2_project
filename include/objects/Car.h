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


  void update(sf::Time time);
  void draw(sf::RenderTarget& window, sf::RenderStates state)const override;

  sf::FloatRect getGlobalBounds() const override;
  std::array<sf::Vector2f, 4> getCorners() const override;
  sf::Angle getAngle()const override;

  bool isStand()const;

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
  sf::Sprite m_wheelR;
  sf::Sprite m_wheelL;
  float              m_angleWheel;
  float              m_heading;
  float              m_speed;
};
