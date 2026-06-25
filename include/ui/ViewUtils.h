#pragma once

#include <SFML/Graphics.hpp>

namespace viewUtils
{
  // Returns a viewport (0..1) that letterboxes a logical area of ratio
  // logicalW/logicalH inside winSize, scaling content to fit without stretch.
  sf::FloatRect letterboxViewport(float logicalW, float logicalH,
                                  sf::Vector2u winSize);
}
