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
  if (!m_textures[Objects::PLAYER_CAR].loadFromFile(AssetPaths::Objects::PLAYER_CAR)) {
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::PLAYER_CAR);
  }
  if (!m_textures[Objects::PARKED_CAR].loadFromFile(AssetPaths::Objects::PARKED_CAR)) {
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::PARKED_CAR);
  }
  if (!m_textures[Objects::PARKING_SPOT].loadFromFile(AssetPaths::Objects::PARKING_SPOT)) {
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::PARKING_SPOT);
  }
  if (!m_textures[Objects::WALL].loadFromFile(AssetPaths::Objects::WALL)) {
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::WALL);
  }
  if (!m_textures[Objects::CONE].loadFromFile(AssetPaths::Objects::CONE)) {
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::CONE);
  }
  if (!m_textures[Objects::BARRIER].loadFromFile(AssetPaths::Objects::BARRIER)) {
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::BARRIER);
  }
  if (!m_textures[Objects::GROUND].loadFromFile(AssetPaths::Objects::GROUND)) {
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::GROUND);
  }
  if (!m_textures[Objects::GRASS_ISLAND].loadFromFile(AssetPaths::Objects::GRASS_ISLAND)) {
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::GRASS_ISLAND);
  }
  if (!m_textures[Objects::WHEEL].loadFromFile(AssetPaths::Objects::WHEEL)) {
    throw std::runtime_error("Failed to load texture: " + AssetPaths::Objects::WHEEL);
  }
}

const sf::Texture& ResourceManager::getTexture(const Objects& key) {
  auto it = m_textures.find(key);
  if (it != m_textures.end()) {
    return it->second;
  }

  throw std::runtime_error("Texture not found for requested key");
}