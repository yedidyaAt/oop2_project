#include "SoundManager.h"
#include <SFML/Audio.hpp>

#include "AssetPaths.h"
#include "AudioSettings.h"

SoundManager::SoundManager() {}

SoundManager& SoundManager::getInstance() {
  static SoundManager instance;
  return instance;
}

void SoundManager::playEffectSound(Sounds key)
{
  cleanupFinished();

  m_sounds.emplace_back(ResourceManager::getInstance().getSound(key));
  m_sounds.back().setVolume(audioCfg::EFFECT_VOLUME);
  m_sounds.back().play();
}

void SoundManager::cleanupFinished()
{
  std::erase_if(m_sounds, [](const sf::Sound& s)
  {
    return s.getStatus() == sf::Sound::Status::Stopped;
  });
}

void SoundManager::playMusic(Musics key, bool forceRestart)
{
  // already playing this track -> do nothing
  if (!forceRestart
    && m_currentTrack.has_value() && *m_currentTrack == key
    && m_music.getStatus() == sf::Music::Status::Playing)
    return;

  std::string path;
  switch (key)
  {
  case Musics::GAME:    path = AssetPaths::Musics::GAME;    break;
  case Musics::OPENING: path = AssetPaths::Musics::OPENING; break;
  case Musics::CREDITS: path = AssetPaths::Musics::CREDITS; break;
  default: throw std::runtime_error("Unknown music key");
  }

  if (!m_music.openFromFile(path))
    throw std::runtime_error("Failed to open music: " + path);

  m_music.setLooping(true);
  m_music.setVolume(audioCfg::MUSIC_VOLUME);
  m_music.play();
  m_currentTrack = key;
}

void SoundManager::pauseMusic()
{
  if (m_music.getStatus() == sf::Music::Status::Playing)
    m_music.pause();
}

void SoundManager::resumeMusic()
{
  if (m_music.getStatus() == sf::Music::Status::Paused)
    m_music.play();
}

void SoundManager::stopMusic()
{
  m_music.stop();
  m_currentTrack.reset();
}

bool SoundManager::isMusicPlaying() const
{
  return m_music.getStatus() == sf::Music::Status::Playing;
}
