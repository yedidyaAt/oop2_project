#pragma once

#include <SFML/Graphics.hpp>


class GameObject: public sf::Drawable
{
public:
  GameObject(const sf::Texture& texture, const sf::Vector2f& pos);
  virtual ~GameObject() = default;

  virtual void update(sf::Time time) = 0;
  virtual sf::FloatRect getGlobalBounds() const= 0;

  virtual std::array<sf::Vector2f, 4> getCorners() const = 0;

protected:
  sf::Sprite m_sprite;
};