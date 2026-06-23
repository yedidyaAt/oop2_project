#include "SoundManager.h"
#include <SFML/Audio.hpp> 

#include "AssetPaths.h"


SoundManager::SoundManager() {}

SoundManager& SoundManager::getInstance() {
	static SoundManager instance;
	return instance;
}

void SoundManager::playEffectSound(Sounds key)
{
	m_sounds.emplace_back(ResourceManager::getInstance().getSound(key));
	m_sounds.back().play();
	m_sounds.back().setVolume(15.0f);
}

void SoundManager::playMusic(Musics key)
{
    std::string path;
    switch (key)
    {
    case Musics::GAME:
        path = AssetPaths::Musics::GAME;
        break;
    case Musics::OPENING:
        path = AssetPaths::Musics::OPENING;
        break;
    default:
        throw std::runtime_error("Unknown music key");
    }

    if (!m_music.openFromFile(path))
        throw std::runtime_error("Failed to open music: " + path);

    m_music.setLooping(true);
    m_music.play();
}