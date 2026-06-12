#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

#include "Objects.h"

class ResourceManager {
public:
  static ResourceManager& getInstance();

  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  void load();
  const sf::Texture& getTexture(const Objects& key);

private:
  ResourceManager();
  std::unordered_map<Objects, sf::Texture> m_textures;
};