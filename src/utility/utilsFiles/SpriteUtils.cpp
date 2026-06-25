#include "SpriteUtils.h"

void spriteUtils::fitToSize(sf::Sprite& s, const float x)
{
  float scale = x / static_cast<float>(s.getTexture().getSize().x);
  s.setScale(sf::Vector2f{scale,scale});
}
