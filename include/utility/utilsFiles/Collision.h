#pragma once

#include <SFML/Graphics.hpp>


namespace collision
{
  // Shrinks each object's collision box to this fraction of its sprite
  // bounds, around the box center. Compensates for transparent padding
  // in the PNGs so collisions match what's visually drawn.
  // 1.0 = full bounds (touching padding counts). 0.95 = 5% tighter.
  constexpr float HITBOX_SCALE = 0.85f;

  std::array<sf::Vector2f,4> getGlobalPoints(const sf::FloatRect& rec,const sf::Transform& trans);

  bool overlaps(const std::array<sf::Vector2f, 4>& a,
                const std::array<sf::Vector2f, 4>& b);

}
