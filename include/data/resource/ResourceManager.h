#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdexcept>
#include <string>

#include "Objects.h"
#include "Sounds.h"
#include "Fonts.h"
#include "UITextures.h"

class ResourceManager {
public:
  static ResourceManager& getInstance();

  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  void load();
  const sf::Texture& getTexture(const Objects& key);
  const sf::Texture& getUITexture(const UITextures& key);
  const sf::SoundBuffer& getSound(const Sounds& key);
  const sf::Font& getFont(const Fonts& key);

private:
  ResourceManager();
  std::unordered_map<Objects, sf::Texture> m_textures;
  std::unordered_map<UITextures, sf::Texture> m_uiTextures;
  std::unordered_map<Sounds, sf::SoundBuffer> m_sound;
  std::unordered_map<Fonts, sf::Font> m_fonts;
};
