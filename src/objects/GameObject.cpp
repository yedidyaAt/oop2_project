#include "GameObject.h"

GameObject::GameObject(const sf::Texture& texture, float posX, float posY):
  m_sprite(texture)
{
  m_sprite.setPosition({ posX,posY });
}
