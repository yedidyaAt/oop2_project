#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include <optional>

#include "ResourceManager.h"
#include "Sounds.h"
#include "Musics.h"

class SoundManager {
public:
  static SoundManager& getInstance();

  SoundManager(const SoundManager&) = delete;
  SoundManager& operator=(const SoundManager&) = delete;

  void playEffectSound(sounds key);

  // Starts a track only if it is not already the one playing (so re-entering
  // the menu does not restart the opening music).
  void playMusic(musics key, bool forceRestart = false);

  void pauseMusic();
  void resumeMusic();
  void stopMusic();
  bool isMusicPlaying() const;

  // Removes finished sounds so the internal vector does not grow forever.
  void cleanupFinished();

private:
  SoundManager();
  std::vector<sf::Sound> m_sounds;
  sf::Music m_music;
  std::optional<musics> m_currentTrack;
};
