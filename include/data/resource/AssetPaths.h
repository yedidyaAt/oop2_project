// AssetPaths.h
#pragma once
#include <string>

namespace AssetPaths {
  inline const std::string IMAGES_DIR = "resources/images/object/";

  namespace Objects {
    inline const std::string PLAYER_CAR   = IMAGES_DIR + "car_player.png";
    inline const std::string PARKED_CAR   = IMAGES_DIR + "parking_car.png";
    inline const std::string PARKING_SPOT = IMAGES_DIR + "parking_spot.png";
    inline const std::string WALL         = IMAGES_DIR + "wall.png";
    inline const std::string CONE         = IMAGES_DIR + "cone.png";
    inline const std::string BARRIER      = IMAGES_DIR + "barrier.png";
    inline const std::string GROUND       = IMAGES_DIR + "ground.png";
    inline const std::string GRASS_ISLAND = IMAGES_DIR + "grass_island.png";
    inline const std::string PARKING      = IMAGES_DIR + "parking.png";
    inline const std::string CROSSING     = IMAGES_DIR + "crossing.png";
    inline const std::string LANE_DIVIDER = IMAGES_DIR + "lane_divider.png";
    inline const std::string WHEEL        = IMAGES_DIR + "wheel.png";
  }

  inline const std::string UI_DIR = "resources/ui/";

  namespace UI {
    inline const std::string MENU_BG     = UI_DIR + "menu_bg.png";
    inline const std::string LEVELS_BG   = UI_DIR + "levels_bg.png";
    inline const std::string STAR_FILLED = UI_DIR + "star_filled.png";
    inline const std::string STAR_EMPTY  = UI_DIR + "star_empty.png";
    inline const std::string LOCK        = UI_DIR + "lock.png";
  }

  inline const std::string FONTS_DIR = "resources/fonts/";

  namespace Fonts {
    inline const std::string MAIN = FONTS_DIR + "main.ttf";
  }

  inline const std::string SOUND_DIR = "resources/sounds/";

  namespace Sounds {
      inline const std::string CLICKING_BUTTON = SOUND_DIR + "Clicking_a_button.wav";
      inline const std::string COLLISION       = SOUND_DIR + "collision.wav";
      inline const std::string END_OF_GAME     = SOUND_DIR + "end_of_game.wav";
      inline const std::string END_OF_STAGE    = SOUND_DIR + "end_of_stage.wav";
  }

  inline const std::string MUSIC_DIR = "resources/music/";

  namespace Musics {
      inline const std::string GAME    = MUSIC_DIR + "game.wav";
      inline const std::string OPENING = MUSIC_DIR + "opening.wav";
      inline const std::string CREDITS = MUSIC_DIR + "credits.mp3";
  }
}
