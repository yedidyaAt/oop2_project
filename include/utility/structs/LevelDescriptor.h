#pragma once

#include "ObjectDescriptor.h"

#include <vector>

struct LevelDescriptor
{
  std::string                   m_nameLevel;
  ObjectDescriptor              m_car;
  ObjectDescriptor              m_target;
  std::vector<ObjectDescriptor> m_objects;
};
