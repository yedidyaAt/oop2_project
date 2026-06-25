#include "Playlist.h"


#include "json.hpp"

#include "FileUtils.h"

Playlist::Playlist(){}

std::vector<std::string> Playlist::getPlaylist(const std::string& path) const
{
  using json = nlohmann::json;

  std::vector<std::string> listVec;

  try {
    std::ifstream file = fileUtils::openForReading(path);

    json jFile = json::parse(file);

    for (const auto& nameFile : jFile.at("levels"))
    {
      listVec.emplace_back(nameFile.get<std::string>());
    }

  }
  catch (const json::exception& e)
  {
    throw std::runtime_error(std::string(path) + e.what());
  }

  return listVec;
}
