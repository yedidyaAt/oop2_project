#include "ResourceManager.h"
#include <exception>

ResourceManager::ResourceManager() {}


ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;
	return instance;
}


void ResourceManager::load()
{
	//Objects
	if (!m_textures[Objects::PLAYER_CAR].loadFromFile("resources/car_player.png")) {
		throw std::runtime_error("Failed to load texture: resources/car_player.png");
	}
	if (!m_textures[Objects::PARKED_CAR].loadFromFile("resources/parking_car.png")) {
		throw std::runtime_error("Failed to load texture: resources/parking_car.png");
	}
	if (!m_textures[Objects::PARKING_SPOT].loadFromFile("resources/parking_stop.png")) {
		throw std::runtime_error("Failed to load texture: resources/parking_stop.png");
	}
	if (!m_textures[Objects::WALL].loadFromFile("resources/wall.png")) {
		throw std::runtime_error("Failed to load texture: resources/wall.png");
	}
	if (!m_textures[Objects::CONE].loadFromFile("resources/cone.png")) {
		throw std::runtime_error("Failed to load texture: resources/cone.png");
	}
	if (!m_textures[Objects::BARRIER].loadFromFile("resources/barrier.png")) {
		throw std::runtime_error("Failed to load texture: resources/barrier.png");
	}
	if (!m_textures[Objects::GROUND].loadFromFile("resources/ground.png")) {
		throw std::runtime_error("Failed to load texture: resources/ground.png");
	}
	if (!m_textures[Objects::GRASS_ISLAND].loadFromFile("resources/grass_island.png")) {
		throw std::runtime_error("Failed to load texture: resources/grass_island.png");
	}
}

const sf::Texture& ResourceManager::getTexture(const Objects& key)
{
	auto it = m_textures.find(key);
	if (it != m_textures.end())
	{
		return it->second;
	}

	throw std::runtime_error("fack you");
}


