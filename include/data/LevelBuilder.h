#pragma once

#include "LevelData.h"

class LevelBuilder
{
public:
  LevelBuilder() = default;

  LevelData buildLevel(const std::string& path)const;

private:
  std::unique_ptr<Car> castFromGameObject(std::unique_ptr<GameObject> obj)const;
};