#include "LevelBuilder.h"

#include <utility>

#include "Loader.h"
#include "LevelDescriptor.h"
#include "Factory.h"


LevelData LevelBuilder::buildLevel(const std::string& path) const
{
  const auto LevelDes = Loader().getData(path);

  //=============================================
  //===== START AT BUILD&SORT INTO LEVEL DATA ===
  //=============================================
  LevelData levelData;

  //============= BUILD CAR ===================
  levelData.m_car = castFromGameObject(factory::create(LevelDes.m_car));

  //============= BUILD TARGET ===================
  levelData.m_target = factory::create(LevelDes.m_target);

  //============= BUILD OBJECTS ===================
  for (auto& objDes : LevelDes.m_objects)
  {
    auto obj = factory::create(objDes);

    if (obj->isBlocks())
      levelData.m_blocksObj.emplace_back(std::move(obj));
    else
      levelData.m_decalsObj.emplace_back(std::move(obj));
  }


  return levelData;
}

std::unique_ptr<Car> LevelBuilder::castFromGameObject(std::unique_ptr<GameObject> obj) const
{
  Car* carPtr = dynamic_cast<Car*>(obj.get());

  if (carPtr)
  {
    return std::unique_ptr<Car>(static_cast<Car*>(obj.release()));
  }
  else
  {
    throw std::runtime_error("LevelBuilder error: Player car is not of type Car!");
  }
}
