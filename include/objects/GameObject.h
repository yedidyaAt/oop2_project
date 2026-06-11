#pragma once

#include <SFML/Graphics.hpp>

class GameObject: public sf::Drawable
{
public:

  GameObject(const sf::Texture& texture, float posX,float posY);
  virtual ~GameObject() = default;

  virtual void update(float timeLeft) = 0;

private:
  sf::Sprite m_sprite;
};