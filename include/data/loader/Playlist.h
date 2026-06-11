#pragma once

#include <string>
#include <fstream>
#include <vector>

class Playlist
{
public:
  explicit Playlist();

  std::vector<std::string> getPlaylist(const std::string& path)const;

private:

};