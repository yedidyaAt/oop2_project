#include "Objectutils.h"

Objects objectUtils::getObjectConversionByStr(const std::string& objStr)
{
  static const std::unordered_map<std::string, Objects> table = {
      {"player_car",   Objects::PLAYER_CAR},
      {"parked_car",   Objects::PARKED_CAR},
      {"parking_spot", Objects::PARKING_SPOT},
      {"wall",         Objects::WALL},
      {"cone",         Objects::CONE},
      {"barrier",      Objects::BARRIER},
      {"ground",       Objects::GROUND},
      {"grass_island", Objects::GRASS_ISLAND},
      {"parking",      Objects::PARKING},
      {"crossing",     Objects::CROSSING},
      {"lane_divider", Objects::LANE_DIVIDER}
  };

   return table.at(objStr);
}
