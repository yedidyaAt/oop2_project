#pragma once

#include <SFML/Graphics.hpp>


namespace collision
{
  std::array<sf::Vector2f,4> getGlobalPoints(const sf::FloatRect& rec,const sf::Transform& trans);

  bool overlaps(const std::array<sf::Vector2f, 4>& a,
                const std::array<sf::Vector2f, 4>& b);

}
