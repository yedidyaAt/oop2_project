#pragma once

#include <vector>
#include <memory>

#include "GameObject.h"
#include "Car.h"

struct LevelData
{
  std::vector<std::unique_ptr<GameObject>> m_blocksObj = std::vector<std::unique_ptr<GameObject>>();
  std::vector<std::unique_ptr<GameObject>> m_decalsObj = std::vector<std::unique_ptr<GameObject>>();
  std::unique_ptr<GameObject> m_car = std::unique_ptr<GameObject>();
};