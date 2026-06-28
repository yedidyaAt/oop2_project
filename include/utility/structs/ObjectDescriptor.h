#pragma once

#include "Objects.h"

struct ObjectDescriptor
{
  ObjectDescriptor() = default;
  ObjectDescriptor(objects type, float x, float y,float angle) :
    m_type(type),
    m_x(x),
    m_y(y),
    m_angle(angle)
  {}

  objects  m_type;
  float m_x, m_y;
  float m_angle;
};
