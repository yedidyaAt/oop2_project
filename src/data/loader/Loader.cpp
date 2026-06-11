#include "Loader.h"


#include "json.hpp"

#include "fileutils.h"

#include <exception>



Loader::Loader()
{
}

LevelData Loader::getData(const std::string& path)const
{
  using json = nlohmann::json;

  std::ifstream file = fileutils::openForReading(path);
  LevelData levelData;

  try {
    json jFile = json::parse(file);

    levelData.m_nameLevel = path;
    
    for (const auto& obj : jFile.at("objects"))
    {
      levelData.m_objects.emplace_back(
        obj.at("type").get<std::string>(),
        obj.at("x").get<int>(),
        obj.at("y").get<int>()
        );
    }

  }
  catch (const json::exception& e)
  {
    throw std::runtime_error(std::string(path) + e.what());
  }

  return levelData;// do the optemize auto 
}

