#pragma once

#include "ObjectDescriptor.h"

#include <vector>

struct LevelData
{
  std::string m_nameLevel;
  std::vector<ObjectDescriptor> m_objects;
};
