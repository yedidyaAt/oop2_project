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
  if (!m_texturesObjects[objects::PLAYER_CAR].loadFromFile(assetPaths::objects::PLAYER_CAR))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::PLAYER_CAR);
  if (!m_texturesObjects[objects::PARKED_CAR].loadFromFile(assetPaths::objects::PARKED_CAR))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::PARKED_CAR);
  if (!m_texturesObjects[objects::PARKING_SPOT].loadFromFile(assetPaths::objects::PARKING_SPOT))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::PARKING_SPOT);
  if (!m_texturesObjects[objects::WALL].loadFromFile(assetPaths::objects::WALL))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::WALL);
  if (!m_texturesObjects[objects::CONE].loadFromFile(assetPaths::objects::CONE))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::CONE);
  if (!m_texturesObjects[objects::BARRIER].loadFromFile(assetPaths::objects::BARRIER))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::BARRIER);
  if (!m_texturesObjects[objects::GROUND].loadFromFile(assetPaths::objects::GROUND))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::GROUND);
  if (!m_texturesObjects[objects::GRASS_ISLAND].loadFromFile(assetPaths::objects::GRASS_ISLAND))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::GRASS_ISLAND);
  if (!m_texturesObjects[objects::WHEEL].loadFromFile(assetPaths::objects::WHEEL))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::WHEEL);
  if (!m_texturesObjects[objects::PARKING].loadFromFile(assetPaths::objects::PARKING))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::PARKING);
  if (!m_texturesObjects[objects::CROSSING].loadFromFile(assetPaths::objects::CROSSING))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::CROSSING);
  if (!m_texturesObjects[objects::LANE_DIVIDER].loadFromFile(assetPaths::objects::LANE_DIVIDER))
    throw std::runtime_error("Failed to load texture: " + assetPaths::objects::LANE_DIVIDER);

  //Effects
  if (!m_texturesEffects[Effects::SMOKE].loadFromFile(assetPaths::animation::SMOKE_TILE_SHEET))
    throw std::runtime_error("Failed to load texture: " + assetPaths::animation::SMOKE_TILE_SHEET);

  //UI textures
  if (!m_uiTextures[UITextures::MENU_BG].loadFromFile(assetPaths::ui::MENU_BG))
    throw std::runtime_error("Failed to load UI texture: " + assetPaths::ui::MENU_BG);
  if (!m_uiTextures[UITextures::LEVELS_BG].loadFromFile(assetPaths::ui::LEVELS_BG))
    throw std::runtime_error("Failed to load UI texture: " + assetPaths::ui::LEVELS_BG);
  if (!m_uiTextures[UITextures::STAR_FILLED].loadFromFile(assetPaths::ui::STAR_FILLED))
    throw std::runtime_error("Failed to load UI texture: " + assetPaths::ui::STAR_FILLED);
  if (!m_uiTextures[UITextures::STAR_EMPTY].loadFromFile(assetPaths::ui::STAR_EMPTY))
    throw std::runtime_error("Failed to load UI texture: " + assetPaths::ui::STAR_EMPTY);
  if (!m_uiTextures[UITextures::LOCK].loadFromFile(assetPaths::ui::LOCK))
    throw std::runtime_error("Failed to load UI texture: " + assetPaths::ui::LOCK);

  //Sound
  if (!m_sound[sounds::CLICKING_BUTTON].loadFromFile(assetPaths::sounds::CLICKING_BUTTON))
      throw std::runtime_error("Failed to load Sound: " + assetPaths::sounds::CLICKING_BUTTON);
  if (!m_sound[sounds::COLLISION].loadFromFile(assetPaths::sounds::COLLISION))
      throw std::runtime_error("Failed to load Sound: " + assetPaths::sounds::COLLISION);
  if (!m_sound[sounds::END_OF_GAME].loadFromFile(assetPaths::sounds::END_OF_GAME))
      throw std::runtime_error("Failed to load Sound: " + assetPaths::sounds::END_OF_GAME);
  if (!m_sound[sounds::END_OF_STAGE].loadFromFile(assetPaths::sounds::END_OF_STAGE))
      throw std::runtime_error("Failed to load Sound: " + assetPaths::sounds::END_OF_STAGE);

  //Fonts
  if (!m_fonts[fonts::MAIN].openFromFile(assetPaths::fonts::MAIN))
      throw std::runtime_error("Failed to load Font: " + assetPaths::fonts::MAIN);
}

const sf::Texture& ResourceManager::getTextureObject(const objects& key) {
  auto it = m_texturesObjects.find(key);
  if (it != m_texturesObjects.end()) return it->second;
  throw std::runtime_error("Texture not found for requested key");
}

const sf::Texture& ResourceManager::getTextureEffects(const Effects& key)
{
  auto it = m_texturesEffects.find(key);
  if (it != m_texturesEffects.end()) return it->second;
  throw std::runtime_error("Texture not found for requested key");
}

const sf::Texture& ResourceManager::getUITexture(const UITextures& key) {
  auto it = m_uiTextures.find(key);
  if (it != m_uiTextures.end()) return it->second;
  throw std::runtime_error("UI texture not found for requested key");
}

const sf::SoundBuffer& ResourceManager::getSound(const sounds& key) {
  auto it = m_sound.find(key);
  if (it != m_sound.end()) return it->second;
  throw std::runtime_error("Sounds not found for requested key");
}

const sf::Font& ResourceManager::getFont(const fonts& key) {
  auto it = m_fonts.find(key);
  if (it != m_fonts.end()) return it->second;
  throw std::runtime_error("Font not found for requested key");
}
