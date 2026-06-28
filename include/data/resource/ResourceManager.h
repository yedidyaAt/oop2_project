#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdexcept>
#include <string>

#include "Objects.h"
#include "Effects.h"
#include "Sounds.h"
#include "Fonts.h"
#include "UITextures.h"

class ResourceManager {
public:
  static ResourceManager& getInstance();

  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  void load();
  const sf::Texture& getTextureObject(const objects& key);
  const sf::Texture& getTextureEffects(const Effects& key);
  const sf::Texture& getUITexture(const UITextures& key);
  const sf::SoundBuffer& getSound(const sounds& key);
  const sf::Font& getFont(const fonts& key);

private:
  ResourceManager();
  std::unordered_map<objects, sf::Texture> m_texturesObjects;
  std::unordered_map<Effects, sf::Texture> m_texturesEffects;
  std::unordered_map<UITextures, sf::Texture> m_uiTextures;
  std::unordered_map<sounds, sf::SoundBuffer> m_sound;
  std::unordered_map<fonts, sf::Font> m_fonts;
};
