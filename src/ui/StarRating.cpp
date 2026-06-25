#include "StarRating.h"

#include "ResourceManager.h"
#include "UITextures.h"
#include "UISettings.h"
#include "SpriteUtils.h"

StarRating::StarRating(int stars, sf::Vector2f center)
{
  const int total = ui::MAX_STARS;
  const float step = ui::STAR_SIZE + ui::STAR_GAP;
  const float rowWidth = total * ui::STAR_SIZE + (total - 1) * ui::STAR_GAP;
  const float startX = center.x - rowWidth / 2.f + ui::STAR_SIZE / 2.f;

  for (int i = 0; i < total; ++i)
  {
    const auto& tex = (i < stars)
      ? ResourceManager::getInstance().getUITexture(UITextures::STAR_FILLED)
      : ResourceManager::getInstance().getUITexture(UITextures::STAR_EMPTY);

    sf::Sprite s(tex);
    spriteUtils::fitToSize(s, ui::STAR_SIZE);
    auto b = s.getLocalBounds();
    s.setOrigin({ b.size.x / 2.f, b.size.y / 2.f });
    s.setPosition({ startX + i * step, center.y });
    m_stars.push_back(s);
  }
}

void StarRating::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  for (const auto& s : m_stars)
    target.draw(s, states);
}
