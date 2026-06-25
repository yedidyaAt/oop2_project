#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

// Draws a row of stars (filled up to the rating, empty after) centered around
// a given point. Uses star_filled.png / star_empty.png.
class StarRating : public sf::Drawable
{
public:
  StarRating(int stars, sf::Vector2f center);

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  std::vector<sf::Sprite> m_stars;
};
