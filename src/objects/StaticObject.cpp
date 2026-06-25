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
      sf::Vector2f{ objDes.m_x, objDes.m_y },
      objectSizes::wall::WIDTH,
      sf::degrees(objDes.m_angle),
      true);
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
      sf::degrees(objDes.m_angle),
      true);
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
      sf::degrees(objDes.m_angle),
      false);
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
      sf::degrees(objDes.m_angle),
      true);
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
      sf::degrees(objDes.m_angle),
      true);
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
      sf::degrees(objDes.m_angle),
      true);
  }
);
//=========== PARKING ==================
static const bool registryParking = factory::registerCreator(
  Objects::PARKING,
  [](const ObjectDescriptor& objDes)
  {
    return std::make_unique<StaticObject>(ResourceManager::getInstance().getTexture(Objects::PARKING),
      sf::Vector2f{ objDes.m_x, objDes.m_y },
      objectSizes::parking::WIDTH,
      sf::degrees(objDes.m_angle),
      false);
  }
);
//=========== CROSSING ==================
static const bool registryCrossing = factory::registerCreator(
  Objects::CROSSING,
  [](const ObjectDescriptor& objDes)
  {
    return std::make_unique<StaticObject>(ResourceManager::getInstance().getTexture(Objects::CROSSING),
      sf::Vector2f{ objDes.m_x, objDes.m_y },
      objectSizes::crossing::WIDTH,
      sf::degrees(objDes.m_angle),
      false);
  }
);
//=========== LANE_DIVIDER ==================
static const bool registryLaneDivider = factory::registerCreator(
  Objects::LANE_DIVIDER,
  [](const ObjectDescriptor& objDes)
  {
    return std::make_unique<StaticObject>(ResourceManager::getInstance().getTexture(Objects::LANE_DIVIDER),
      sf::Vector2f{ objDes.m_x, objDes.m_y },
      objectSizes::laneDivider::WIDTH,
      sf::degrees(objDes.m_angle),
      false);
  }
);

//=====================================
//           END REGISTERS
//=====================================






StaticObject::StaticObject(const sf::Texture& texture, const sf::Vector2f& pos,
                                                float fitSize, sf::Angle angle,
                                                bool block) :
  GameObject(texture, pos,block)
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
    return collision::getGlobalPoints(m_sprite.getLocalBounds(),m_sprite.getTransform());
}

sf::Angle StaticObject::getAngle() const
{
    return m_sprite.getRotation();
}

void StaticObject::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
  target.draw(m_sprite, state);
}
