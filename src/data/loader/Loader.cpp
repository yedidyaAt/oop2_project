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

    //========= LOAD CAR ==========
    const auto carDes = jFile.at("car");
    Objects typeCarObj = objectUtils::getObjectConversionByStr(carDes.at("type").get<std::string>());

    levelDes.m_car = {
      typeCarObj,
      carDes.at("x").get<float>(),
      carDes.at("y").get<float>(),
      carDes.value("rotation", 0.0f)
    };

    //========= LOAD TARGET(PARKING SPOT) ==========
    const auto targetDes = jFile.at("target");
    Objects typeTargetObj = objectUtils::getObjectConversionByStr(targetDes.at("type").get<std::string>());

    levelDes.m_target = {
      typeTargetObj,
      targetDes.at("x").get<float>(),
      targetDes.at("y").get<float>(),
      targetDes.value("rotation", 0.0f)
    };

    //========= LOAD OTHER OBJECTS ==========
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

  return levelDes;
}
