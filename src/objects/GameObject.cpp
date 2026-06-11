#include "GameObject.h"

GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& pos):
  m_sprite(texture)
{
  m_sprite.setPosition(pos);
}
