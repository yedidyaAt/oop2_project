#pragma once

#include<string>

struct ObjectDescriptor
{
  ObjectDescriptor(const std::string& type, int x, int y) :
    m_type(type),
    m_x(x),
    m_y(y)
  {}

  std::string m_type;
  int m_x, m_y;
};