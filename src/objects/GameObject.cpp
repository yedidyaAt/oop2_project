#include "GameObject.h"

GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& pos,bool block):
  m_sprite(texture),
  m_block(block)
{
  m_sprite.setPosition(pos);
}

bool GameObject::isBlocks() const
{
  return m_block;
}
