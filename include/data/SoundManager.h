#pragma once

#include <SFML/Audio.hpp> 
#include <vector>

#include "ResourceManager.h"
#include "Sounds.h"
#include "Musics.h"

class SoundManager {
public:
	static SoundManager& getInstance();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	void playEffectSound(Sounds key);
	void playMusic(Musics key);

private:
	SoundManager();
	std::vector<sf::Sound> m_sounds;
	sf::Music m_music;
};