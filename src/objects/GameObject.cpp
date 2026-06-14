#include "GameObject.h"



GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& pos,const float sizex):
  m_sprite(texture)
{
	spriteutils::fitToSize(m_sprite, sizex);
  m_sprite.setPosition(pos);
}
