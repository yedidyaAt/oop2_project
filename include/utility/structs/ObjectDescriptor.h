#pragma once

#include "Objects.h"

struct ObjectDescriptor
{
  ObjectDescriptor() = default;
  ObjectDescriptor(Objects type, float x, float y,float angle) :
    m_type(type),
    m_x(x),
    m_y(y),
    m_angle(angle)
  {}

  Objects  m_type;
  float m_x, m_y;
  float m_angle;
};
