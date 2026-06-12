#include "Wall.h"

Wall::Wall(const sf::Texture& texture, const sf::Vector2f& pos) :
  GameObject(texture, pos){}

void Wall::update(sf::Time time)
{
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
  target.draw(m_sprite, state);
}
