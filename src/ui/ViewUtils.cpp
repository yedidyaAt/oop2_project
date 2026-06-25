#include "ui/ViewUtils.h"

sf::FloatRect viewUtils::letterboxViewport(float logicalW, float logicalH,
                                           sf::Vector2u winSize)
{
  float windowRatio  = static_cast<float>(winSize.x) / static_cast<float>(winSize.y);
  float logicalRatio = logicalW / logicalH;

  float sizeX = 1.f, sizeY = 1.f, posX = 0.f, posY = 0.f;

  if (windowRatio > logicalRatio)
  {
    sizeX = logicalRatio / windowRatio;
    posX  = (1.f - sizeX) / 2.f;
  }
  else
  {
    sizeY = windowRatio / logicalRatio;
    posY  = (1.f - sizeY) / 2.f;
  }

  return sf::FloatRect({ posX, posY }, { sizeX, sizeY });
}
