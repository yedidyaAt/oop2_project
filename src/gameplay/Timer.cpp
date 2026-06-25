#include "Timer.h"

void Timer::reset()
{
  m_elapsed = 0.f;
}

void Timer::tick(sf::Time dt)
{
  m_elapsed += dt.asSeconds();
}

float Timer::elapsedSeconds() const
{
  return m_elapsed;
}
