#pragma once

#include <SFML/System/Time.hpp>

// A simple stopwatch that counts UP. Accumulates elapsed seconds while the
// level is being played; can be paused (by simply not calling tick) and reset.
class Timer
{
public:
  Timer() = default;

  void reset();
  void tick(sf::Time dt);

  float elapsedSeconds() const;

private:
  float m_elapsed = 0.f;
};
