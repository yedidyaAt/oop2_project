#pragma once

#include "LevelData.h"

class LevelBuilder
{
public:
  LevelBuilder() = default;

  LevelData buildLevel(const std::string& path)const;
};