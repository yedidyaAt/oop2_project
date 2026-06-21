#pragma once

#include <SFML/Graphics.hpp>


class GameObject: public sf::Drawable
{
public:
  GameObject(const sf::Texture& texture, const sf::Vector2f& pos,bool block);
  virtual ~GameObject() = default;

  virtual void update(sf::Time time) = 0;
  virtual sf::FloatRect getGlobalBounds() const= 0;

  virtual std::array<sf::Vector2f, 4> getCorners() const = 0;

  bool isBlocks()const;
protected:
  sf::Sprite m_sprite;
  bool       m_block;
};