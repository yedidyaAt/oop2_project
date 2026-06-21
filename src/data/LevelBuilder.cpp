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
  levelData.m_car = factory::create(LevelDes.m_car);

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
