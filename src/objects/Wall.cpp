#include "Wall.h"

#include <memory>

#include "ResourceManager.h"
#include "Factory.h"

//register
static const bool registery = factory::registerCreator(
  Objects::WALL,
  [](const ObjectDescriptor& objDes)
  {
    return std::make_unique<Wall>(sf::Vector2f{ objDes.m_x, objDes.m_y });
  }
);



Wall::Wall(const sf::Vector2f& pos) :
  GameObject(ResourceManager::getInstance().getTexture(Objects::WALL), pos) { }

void Wall::update(sf::Time /*time*/)
{
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
  target.draw(m_sprite, state);
}
