#include "ObjectUtils.h"

objects objectUtils::getObjectConversionByStr(const std::string& objStr)
{
  static const std::unordered_map<std::string, objects> table = {
      {"player_car",   objects::PLAYER_CAR},
      {"parked_car",   objects::PARKED_CAR},
      {"parking_spot", objects::PARKING_SPOT},
      {"wall",         objects::WALL},
      {"cone",         objects::CONE},
      {"barrier",      objects::BARRIER},
      {"grass_island", objects::GRASS_ISLAND},
      {"parking",      objects::PARKING},
      {"crossing",     objects::CROSSING},
      {"lane_divider", objects::LANE_DIVIDER}
  };

   return table.at(objStr);
}
