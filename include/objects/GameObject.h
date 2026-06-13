#pragma once

#include <SFML/Graphics.hpp>
#include "Spriteutils.h"


class GameObject: public sf::Drawable
{
public:
	GameObject(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size);
	virtual ~GameObject() = default;

  virtual void update	(sf::Time time) = 0;

protected:
  sf::Sprite m_sprite;
};