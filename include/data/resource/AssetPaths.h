// AssetPaths.h
#pragma once
#include <string>

namespace AssetPaths {
  // בסיס משותף — תשנה פעם אחת אם המבנה ישתנה
  inline const std::string IMAGES_DIR = "resources/images/object/";

  namespace Objects {
    inline const std::string PLAYER_CAR = IMAGES_DIR + "car_player.png";
    inline const std::string PARKED_CAR = IMAGES_DIR + "parking_car.png";
    inline const std::string PARKING_SPOT = IMAGES_DIR + "parking_spot.png";
    inline const std::string WALL = IMAGES_DIR + "wall.png";
    inline const std::string CONE = IMAGES_DIR + "cone.png";
    inline const std::string BARRIER = IMAGES_DIR + "barrier.png";
    inline const std::string GROUND = IMAGES_DIR + "ground.png";
    inline const std::string GRASS_ISLAND = IMAGES_DIR + "grass_island.png";
    inline const std::string PARKING = IMAGES_DIR + "parking.png";
    inline const std::string CROSSING = IMAGES_DIR + "crossing.png";
    inline const std::string LANE_DIVIDER = IMAGES_DIR + "lane_divider.png";
  }

  // בעתיד תוסיף בלוקים נוספים, לדוגמה:
  // namespace Fonts { inline const std::string MAIN = "resources/fonts/main.ttf"; }
  // namespace Sounds { inline const std::string ENGINE = "resources/sounds/engine.wav"; }
}