#pragma once
#include <string>
#include <fstream>

namespace fileutils {
  std::ifstream openForReading(const std::string& path);
}