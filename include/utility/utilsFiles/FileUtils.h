#pragma once
#include <string>
#include <fstream>

namespace fileUtils {
  std::ifstream openForReading(const std::string& path);
}
