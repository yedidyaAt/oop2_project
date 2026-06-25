#include "HUD.h"

void HUD::setElapsed(float seconds)
{
  m_clock.setElapsed(seconds);
}

void HUD::draw(sf::RenderTarget& target) const
{
  target.draw(m_clock);
}
