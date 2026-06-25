#include "FileUtils.h"

std::ifstream fileUtils::openForReading(const std::string& path)
{
  std::ifstream file(path);

  if (file.fail())
  {
    throw std::runtime_error(std::string("file not found ") + path);
  }

  return file;
}
