#pragma once

#include <string>
#include <fstream>


#include "LevelData.h"


class Loader
{
public:
  explicit Loader();

  LevelData getData(const std::string& path)const;

private:

};