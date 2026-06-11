#include "fileutils.h"

std::ifstream fileutils::openForReading(const std::string& path)
{
  std::ifstream file(path);

  if (file.fail())
  {
    throw std::runtime_error(std::string("file not found ") + path);
  }

  return file; // do the optemize auto 
}
