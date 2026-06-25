#pragma once

#include <string>
#include <fstream>


#include "LevelDescriptor.h"


class Loader
{
public:
  explicit Loader();

  LevelDescriptor getData(const std::string& path)const;
};
