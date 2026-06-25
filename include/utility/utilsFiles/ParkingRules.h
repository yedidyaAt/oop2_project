#pragma once

#include <SFML/System/Angle.hpp>

#include "GameObject.h"

namespace parkingRules
{
  // Car counts as "on" the spot if its center is within this distance
  // (in pixels) of the target center.
  // Compared squared (dx*dx + dy*dy < DISTANCE_OFFSET*DISTANCE_OFFSET) to skip sqrt.
  constexpr float DISTANCE_OFFSET = 30.f;


  // Car counts as "aligned" if the angle difference from the target
  // is smaller than this threshold.
  const sf::Angle ANGLE_OFFSET = sf::degrees(10.f);

  bool isParked(const GameObject& car, const GameObject& target);
}
