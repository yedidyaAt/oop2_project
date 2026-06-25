#include "ParkingRules.h"


namespace parkingRules
{
  static sf::Angle myAbs(sf::Angle angle)
  {
    if (angle < sf::Angle::Zero)
    {
      return -angle;
    }

    return angle;
  }

  static bool anglesAligned(sf::Angle carAngle, sf::Angle targetAngle)
  {
    const auto subtractAngle = (carAngle - targetAngle).wrapSigned();
    return myAbs(subtractAngle) < parkingRules::ANGLE_OFFSET;
  }

  static sf::Vector2f getCenter(const std::array<sf::Vector2f, 4>& rectanglePoints)
  {
    sf::Vector2f temp{};

    for (const auto& point : rectanglePoints)
    {
      temp += point;
    }

    return temp/4.f;
  }

  bool closeEnough(const sf::Vector2f& centerL,const sf::Vector2f& centerR)
  {
    sf::Vector2f vec = centerR - centerL;

    // Compare squared distance to avoid sqrt; equivalent to length <= DISTANCE_OFFSET.
    return vec.lengthSquared() <= parkingRules::DISTANCE_OFFSET* parkingRules::DISTANCE_OFFSET;
  }
}

bool parkingRules::isParked(const GameObject& car, const GameObject& target)
{
  if (!anglesAligned(car.getAngle(), target.getAngle()))
    return false;

  if (!closeEnough(getCenter(car.getCorners()), getCenter(target.getCorners())))
    return false;

  return true;
}
