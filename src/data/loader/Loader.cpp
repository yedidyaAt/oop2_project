#include "Loader.h"


#include "json.hpp"

#include "FileUtils.h"
#include "Objects.h"
#include "ObjectUtils.h"

#include <exception>



Loader::Loader()
{
}

LevelData Loader::getData(const std::string& path)const
{
  using json = nlohmann::json;

  std::ifstream file = fileUtils::openForReading(path);
  LevelData levelData;

  try {
    json jFile = json::parse(file);

    levelData.m_nameLevel = path;
    
    for (const auto& obj : jFile.at("objects"))
    {
      Objects typeObj = objectUtils::getObjectConversionByStr(obj.at("type").get<std::string>());
      levelData.m_objects.emplace_back(
        typeObj,
        obj.at("x").get<int>(),
        obj.at("y").get<int>(),
        obj.value("rotation",0.0f)
        );
    }

  }
  catch (const json::exception& e)
  {
    throw std::runtime_error(std::string(path) + e.what());
  }

  return levelData;// do the optemize auto 
}

