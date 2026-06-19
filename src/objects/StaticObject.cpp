#include "StaticObject.h"

#include <memory>

#include "ResourceManager.h"
#include "Factory.h"

#include "SpriteUtils.h"
#include "ObjectSizes.h"

#include "Collision.h"


//=====================================
//            REGISTERS
//=====================================

//=========== WALL ==================
static const bool registeryWall = factory::registerCreator(
  Objects::WALL,
  [](const ObjectDescriptor& objDes)
  {
    return std::make_unique<StaticObject>(ResourceManager::getInstance().getTexture(Objects::WALL),
                                                              sf::Vector2f{objDes.m_x, objDes.m_y},
                                                                         objectSizes::wall::WIDTH,
                                                                         sf::degrees(objDes.m_angle));
  }
);

//=========== PARKED_CAR ==================
static const bool registeryParkedCar = factory::registerCreator(
  Objects::PARKED_CAR,
  [](const ObjectDescriptor& objDes)
  {
    return std::make_unique<StaticObject>(ResourceManager::getInstance().getTexture(Objects::PARKED_CAR),
                                                                  sf::Vector2f{ objDes.m_x, objDes.m_y },
                                                                           objectSizes::parkedCar::WIDTH,
                                                                           sf::degrees(objDes.m_angle));
  }
);

//=========== PARKING_SPOT ==================
static const bool registeryParkingSpot = factory::registerCreator(
  Objects::PARKING_SPOT,
  [](const ObjectDescriptor& objDes)
  {
    return std::make_unique<StaticObject>(ResourceManager::getInstance().getTexture(Objects::PARKING_SPOT),
                                                                    sf::Vector2f{ objDes.m_x, objDes.m_y },
                                                                          objectSizes::parkingSpot::WIDTH,
                                                                          sf::degrees(objDes.m_angle));
  }
);

//=========== CONE ==================
static const bool registeryCone = factory::registerCreator(
  Objects::CONE,
  [](const ObjectDescriptor& objDes)
  {
    return std::make_unique<StaticObject>(ResourceManager::getInstance().getTexture(Objects::CONE),
                                                            sf::Vector2f{ objDes.m_x, objDes.m_y },
                                                                         objectSizes::cone::WIDTH,
                                                                         sf::degrees(objDes.m_angle));
  }
);

//=========== BARRIER ==================
static const bool registeryBarrier = factory::registerCreator(
  Objects::BARRIER,
  [](const ObjectDescriptor& objDes)
  {
    return std::make_unique<StaticObject>(ResourceManager::getInstance().getTexture(Objects::BARRIER),
                                                               sf::Vector2f{ objDes.m_x, objDes.m_y },
                                                                         objectSizes::barrier::WIDTH,
                                                                         sf::degrees(objDes.m_angle));
  }
);

//=========== GRASS_ISLAND ==================
static const bool registeryGrassIsland = factory::registerCreator(
  Objects::GRASS_ISLAND,
  [](const ObjectDescriptor& objDes)
  {
    return std::make_unique<StaticObject>(ResourceManager::getInstance().getTexture(Objects::GRASS_ISLAND),
                                                                    sf::Vector2f{ objDes.m_x, objDes.m_y },
                                                                          objectSizes::grassIsland::WIDTH,
                                                                          sf::degrees(objDes.m_angle));
  }
);

//=====================================
//           END REGISTERS
//=====================================





StaticObject::StaticObject(const sf::Texture& texture, const sf::Vector2f& pos,
                                                float fitSize, sf::Angle angle) :
  GameObject(texture, pos)
{
  spriteUtils::fitToSize(m_sprite, fitSize);

  //origin 
  m_sprite.setOrigin(sf::Vector2f(m_sprite.getLocalBounds().size/2.f));

  m_sprite.setRotation(angle);
  m_sprite.setOrigin({});
}

void StaticObject::update(sf::Time /*time*/)
{
}

sf::FloatRect StaticObject::getGlobalBounds()const
{
    return m_sprite.getGlobalBounds();
}

std::array<sf::Vector2f, 4> StaticObject::getCorners() const
{
    return collision::getGlobalePoints(m_sprite.getLocalBounds(),m_sprite.getTransform());
}

void StaticObject::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
  target.draw(m_sprite, state);
}
