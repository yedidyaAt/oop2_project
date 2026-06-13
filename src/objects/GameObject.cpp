#include "GameObject.h"



GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& pos,const  sf::Vector2f& size):
  m_sprite(texture)
{
  spriteutils::fitToSize(m_sprite, size);
  m_sprite.setPosition(pos);
}
