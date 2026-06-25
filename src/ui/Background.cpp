#include "Background.h"

#include "ResourceManager.h"
#include "DisplaySettings.h"

#include <algorithm>

Background::Background(UITextures which) :
  m_sprite(ResourceManager::getInstance().getUITexture(which))
{
  fitTo({ static_cast<float>(display::WINDOW_WIDTH),
          static_cast<float>(display::WINDOW_HEIGHT) });
}

void Background::fitTo(sf::Vector2f logicalSize)
{
  const auto texSize = m_sprite.getTexture().getSize();
  if (texSize.x == 0 || texSize.y == 0)
    return;

  const float sx = logicalSize.x / static_cast<float>(texSize.x);
  const float sy = logicalSize.y / static_cast<float>(texSize.y);
  const float scale = std::max(sx, sy); // cover (no stretch, fill area)

  m_sprite.setScale({ scale, scale });
  m_sprite.setOrigin({ static_cast<float>(texSize.x) / 2.f,
                       static_cast<float>(texSize.y) / 2.f });
  m_sprite.setPosition({ logicalSize.x / 2.f, logicalSize.y / 2.f });
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_sprite, states);
}
