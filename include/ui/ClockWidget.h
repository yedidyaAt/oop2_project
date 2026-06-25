#pragma once

#include <SFML/Graphics.hpp>

// A little drawn stopwatch shown in the HUD: a circular face with a red hand
// that sweeps around as time passes, plus the elapsed seconds drawn beside it.
class ClockWidget : public sf::Drawable
{
public:
  ClockWidget();

  void setElapsed(float seconds);

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  sf::CircleShape    m_face;
  sf::CircleShape    m_knob;       // top button of the stopwatch
  sf::RectangleShape m_hand;
  sf::Text           m_text;
  float              m_elapsed = 0.f;
};
