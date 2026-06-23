#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <stdexcept>
#include <string>

#include "Objects.h"
#include "Sounds.h"

class ResourceManager {
public:
  static ResourceManager& getInstance();

  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  void load();
  const sf::Texture& getTexture(const Objects& key);
  const sf::SoundBuffer& getSound(const Sounds& key);

private:
  ResourceManager();
  std::unordered_map<Objects, sf::Texture> m_textures;
  std::unordered_map<Sounds, sf::SoundBuffer> m_sound;

};