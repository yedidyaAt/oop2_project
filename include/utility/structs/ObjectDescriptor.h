#pragma once

#include "Objects.h"

struct ObjectDescriptor
{
  ObjectDescriptor(Objects type, int x, int y) :
    m_type(type),
    m_x(x),
    m_y(y)
  {}

  Objects  m_type;
  float m_x, m_y;
};