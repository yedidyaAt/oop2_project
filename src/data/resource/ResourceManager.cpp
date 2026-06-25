#include "ResourceManager.h"
#include "AssetPaths.h"
#include <exception>

ResourceManager::ResourceManager() {}

ResourceManager& ResourceManager::getInstance() {
  static ResourceManager instance;
  return instance;
}

void ResourceManager::load() {
  //Objects
  if (!m_textures[Objects::PLAYER_CAR].loadFromFile(AssetPaths::Objects::PLAYER_CAR))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::PLAYER_CAR);
  if (!m_textures[Objects::PARKED_CAR].loadFromFile(AssetPaths::Objects::PARKED_CAR))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::PARKED_CAR);
  if (!m_textures[Objects::PARKING_SPOT].loadFromFile(AssetPaths::Objects::PARKING_SPOT))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::PARKING_SPOT);
  if (!m_textures[Objects::WALL].loadFromFile(AssetPaths::Objects::WALL))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::WALL);
  if (!m_textures[Objects::CONE].loadFromFile(AssetPaths::Objects::CONE))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::CONE);
  if (!m_textures[Objects::BARRIER].loadFromFile(AssetPaths::Objects::BARRIER))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::BARRIER);
  if (!m_textures[Objects::GROUND].loadFromFile(AssetPaths::Objects::GROUND))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::GROUND);
  if (!m_textures[Objects::GRASS_ISLAND].loadFromFile(AssetPaths::Objects::GRASS_ISLAND))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::GRASS_ISLAND);
  if (!m_textures[Objects::WHEEL].loadFromFile(AssetPaths::Objects::WHEEL))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::WHEEL);
  if (!m_textures[Objects::PARKING].loadFromFile(AssetPaths::Objects::PARKING))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::PARKING);
  if (!m_textures[Objects::CROSSING].loadFromFile(AssetPaths::Objects::CROSSING))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::CROSSING);
  if (!m_textures[Objects::LANE_DIVIDER].loadFromFile(AssetPaths::Objects::LANE_DIVIDER))
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::LANE_DIVIDER);

  //UI textures
  if (!m_uiTextures[UITextures::MENU_BG].loadFromFile(AssetPaths::UI::MENU_BG))
    throw std::runtime_error("Failed to load UI texture: " + AssetPaths::UI::MENU_BG);
  if (!m_uiTextures[UITextures::LEVELS_BG].loadFromFile(AssetPaths::UI::LEVELS_BG))
    throw std::runtime_error("Failed to load UI texture: " + AssetPaths::UI::LEVELS_BG);
  if (!m_uiTextures[UITextures::STAR_FILLED].loadFromFile(AssetPaths::UI::STAR_FILLED))
    throw std::runtime_error("Failed to load UI texture: " + AssetPaths::UI::STAR_FILLED);
  if (!m_uiTextures[UITextures::STAR_EMPTY].loadFromFile(AssetPaths::UI::STAR_EMPTY))
    throw std::runtime_error("Failed to load UI texture: " + AssetPaths::UI::STAR_EMPTY);
  if (!m_uiTextures[UITextures::LOCK].loadFromFile(AssetPaths::UI::LOCK))
    throw std::runtime_error("Failed to load UI texture: " + AssetPaths::UI::LOCK);

  //Sound
  if (!m_sound[Sounds::CLICKING_BUTTON].loadFromFile(AssetPaths::Sounds::CLICKING_BUTTON))
      throw std::runtime_error("Failed to load Sound: " + AssetPaths::Sounds::CLICKING_BUTTON);
  if (!m_sound[Sounds::COLLISION].loadFromFile(AssetPaths::Sounds::COLLISION))
      throw std::runtime_error("Failed to load Sound: " + AssetPaths::Sounds::COLLISION);
  if (!m_sound[Sounds::END_OF_GAME].loadFromFile(AssetPaths::Sounds::END_OF_GAME))
      throw std::runtime_error("Failed to load Sound: " + AssetPaths::Sounds::END_OF_GAME);
  if (!m_sound[Sounds::END_OF_STAGE].loadFromFile(AssetPaths::Sounds::END_OF_STAGE))
      throw std::runtime_error("Failed to load Sound: " + AssetPaths::Sounds::END_OF_STAGE);

  //Fonts
  if (!m_fonts[Fonts::MAIN].openFromFile(AssetPaths::Fonts::MAIN))
      throw std::runtime_error("Failed to load Font: " + AssetPaths::Fonts::MAIN);
}

const sf::Texture& ResourceManager::getTexture(const Objects& key) {
  auto it = m_textures.find(key);
  if (it != m_textures.end()) return it->second;
  throw std::runtime_error("Texture not found for requested key");
}

const sf::Texture& ResourceManager::getUITexture(const UITextures& key) {
  auto it = m_uiTextures.find(key);
  if (it != m_uiTextures.end()) return it->second;
  throw std::runtime_error("UI texture not found for requested key");
}

const sf::SoundBuffer& ResourceManager::getSound(const Sounds& key) {
  auto it = m_sound.find(key);
  if (it != m_sound.end()) return it->second;
  throw std::runtime_error("Sounds not found for requested key");
}

const sf::Font& ResourceManager::getFont(const Fonts& key) {
  auto it = m_fonts.find(key);
  if (it != m_fonts.end()) return it->second;
  throw std::runtime_error("Font not found for requested key");
}
