#include "Loader.h"


#include "json.hpp"

#include "FileUtils.h"
#include "Objects.h"
#include "ObjectUtils.h"

#include <exception>



Loader::Loader()
{
}

LevelDescriptor Loader::getData(const std::string& path)const
{
  using json = nlohmann::json;

  std::ifstream file = fileUtils::openForReading(path);
  LevelDescriptor levelDes;

  try {
    json jFile = json::parse(file);

    levelDes.m_nameLevel = path;

    const auto carDes = jFile.at("car");
    Objects typeObj = objectUtils::getObjectConversionByStr(carDes.at("type").get<std::string>());

    levelDes.m_car = { 
      typeObj,
      carDes.at("x").get<float>(),
      carDes.at("y").get<float>(),
      carDes.value("rotation", 0.0f) 
    };
    
    for (const auto& obj : jFile.at("objects"))
    {
      Objects typeObj = objectUtils::getObjectConversionByStr(obj.at("type").get<std::string>());
      levelDes.m_objects.emplace_back(
        typeObj,
        obj.at("x").get<float>(),
        obj.at("y").get<float>(),
        obj.value("rotation",0.0f)
        );
    }

  }
  catch (const json::exception& e)
  {
    throw std::runtime_error(std::string(path) + e.what());
  }

  return levelDes;// do the optemize auto 
}

