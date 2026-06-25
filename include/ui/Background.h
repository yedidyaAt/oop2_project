#pragma once

#include <SFML/Graphics.hpp>

#include "UITextures.h"

// A full-window background image. Uses "cover" scaling: the image is scaled
// uniformly (no stretch) to cover the logical area, centered.
class Background : public sf::Drawable
{
public:
  explicit Background(UITextures which);

  void fitTo(sf::Vector2f logicalSize);

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  sf::Sprite m_sprite;
};
