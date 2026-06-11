#pragma once

#include <SFML/Graphics.hpp>

class GameObject: public sf::Drawable
{
public:
  GameObject(const sf::Texture& texture, const sf::Vector2f& pos);
  virtual ~GameObject() = default;

  virtual void update(sf::Time time) = 0;

protected:
  sf::Sprite m_sprite;
};