#pragma once

#include <SFML/Graphics.hpp>

#include "ClockWidget.h"

// On-screen heads-up display. Shows the drawn stopwatch (with elapsed time)
// in screen space so it stays fixed even when the world view scrolls.
class HUD
{
public:
  HUD() = default;

  void setElapsed(float seconds);
  void draw(sf::RenderTarget& target) const;

private:
  ClockWidget m_clock;
};
