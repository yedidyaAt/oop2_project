#include<iostream>

#include "Game.h"

#include "Playlist.h"
#include "Loader.h"

int main()
{
  //Game().run();
  Loader loadJson;
  Playlist loadPlaylist;


  try {

    for (const auto& fileName : loadPlaylist.getPlaylist("levels.json"))
    {
      LevelData levelData = loadJson.getData(fileName);

      std::cout << levelData.m_nameLevel << std::endl;

      for (const auto& obj : levelData.m_objects)
      {
        std::cout << obj.m_type << ' '
          << obj.m_x << ' '
          << obj.m_y << std::endl;
      }

      std::cout << std::endl;
    }
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }

}
