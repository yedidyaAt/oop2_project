// AssetPaths.h
#pragma once
#include <string>

namespace assetPaths {
  inline const std::string OBJECTS_DIR = "resources/images/object/";

  namespace objects {
    inline const std::string PLAYER_CAR   = OBJECTS_DIR + "car_player.png";
    inline const std::string PARKED_CAR   = OBJECTS_DIR + "parking_car.png";
    inline const std::string PARKING_SPOT = OBJECTS_DIR + "parking_spot.png";
    inline const std::string WALL         = OBJECTS_DIR + "wall.png";
    inline const std::string CONE         = OBJECTS_DIR + "cone.png";
    inline const std::string BARRIER      = OBJECTS_DIR + "barrier.png";
    inline const std::string GRASS_ISLAND = OBJECTS_DIR + "grass_island.png";
    inline const std::string PARKING      = OBJECTS_DIR + "parking.png";
    inline const std::string CROSSING     = OBJECTS_DIR + "crossing.png";
    inline const std::string LANE_DIVIDER = OBJECTS_DIR + "lane_divider.png";
    inline const std::string WHEEL        = OBJECTS_DIR + "wheel.png";
  }

  inline const std::string ANIMATION_DIR = "resources/images/animation/";

  namespace animation
  {
    inline const std::string SMOKE_TILE_SHEET = ANIMATION_DIR + "smoke_tile_sheet.png";
  }

  inline const std::string UI_DIR = "resources/images/ui/";

  namespace ui {
    inline const std::string MENU_BG     = UI_DIR + "menu_bg.png";
    inline const std::string LEVELS_BG   = UI_DIR + "levels_bg.png";
    inline const std::string STAR_FILLED = UI_DIR + "star_filled.png";
    inline const std::string STAR_EMPTY  = UI_DIR + "star_empty.png";
    inline const std::string LOCK        = UI_DIR + "lock.png";
  }

  inline const std::string FONTS_DIR = "resources/fonts/";

  namespace fonts {
    inline const std::string MAIN = FONTS_DIR + "main.ttf";
  }

  inline const std::string SOUND_DIR = "resources/sounds/";

  namespace sounds {
      inline const std::string CLICKING_BUTTON = SOUND_DIR + "Clicking_a_button.wav";
      inline const std::string COLLISION       = SOUND_DIR + "collision.wav";
      inline const std::string END_OF_GAME     = SOUND_DIR + "end_of_game.wav";
      inline const std::string END_OF_STAGE    = SOUND_DIR + "end_of_stage.wav";
  }

  inline const std::string MUSIC_DIR = "resources/music/";

  namespace musics {
      inline const std::string GAME    = MUSIC_DIR + "game.wav";
      inline const std::string OPENING = MUSIC_DIR + "opening.wav";
      inline const std::string CREDITS = MUSIC_DIR + "credits.mp3";
  }
}
