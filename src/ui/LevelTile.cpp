#include "LevelTile.h"

#include "ResourceManager.h"
#include "Fonts.h"
#include "UITextures.h"
#include "UISettings.h"
#include "SpriteUtils.h"

#include <string>

LevelTile::LevelTile(std::size_t levelNumber, bool unlocked, sf::Vector2f center) :
  m_number(ResourceManager::getInstance().getFont(fonts::MAIN)),
  m_lock(ResourceManager::getInstance().getUITexture(UITextures::LOCK)),
  m_levelNumber(levelNumber),
  m_unlocked(unlocked)
{
  m_box.setSize({ ui::TILE_SIZE, ui::TILE_SIZE });
  m_box.setOrigin({ ui::TILE_SIZE / 2.f, ui::TILE_SIZE / 2.f });
  m_box.setPosition(center);
  m_box.setOutlineThickness(ui::TILE_OUTLINE);
  m_box.setOutlineColor(ui::TILE_OUTLINE_COL);

  m_number.setString(std::to_string(levelNumber));
  m_number.setCharacterSize(ui::HEADING_SIZE);
  m_number.setFillColor(ui::TILE_NUM_COL);
  m_number.setOutlineColor(ui::OUTLINE_COL);
  m_number.setOutlineThickness(2.f);
  {
    auto b = m_number.getLocalBounds();
    m_number.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
    m_number.setPosition(center);
  }

  // lock icon centered, scaled to ~half the tile
  spriteUtils::fitToSize(m_lock, ui::TILE_SIZE * 0.5f);
  {
    auto b = m_lock.getLocalBounds();
    m_lock.setOrigin({ b.size.x / 2.f, b.size.y / 2.f });
    m_lock.setPosition(center);
  }
}

void LevelTile::updateHover(sf::Vector2f mousePos)
{
  m_hovered = m_unlocked && contains(mousePos);
}

bool LevelTile::contains(sf::Vector2f point) const
{
  return m_box.getGlobalBounds().contains(point);
}

bool LevelTile::isUnlocked() const { return m_unlocked; }
std::size_t LevelTile::levelNumber() const { return m_levelNumber; }

void LevelTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  sf::RectangleShape box = m_box;

  if (m_unlocked)
    box.setFillColor(m_hovered ? ui::TILE_UNLOCKED_HOV : ui::TILE_UNLOCKED);
  else
  {
    sf::Color c = ui::TILE_LOCKED;
    c.a = ui::LOCKED_ALPHA;
    box.setFillColor(c);
  }

  target.draw(box, states);

  if (m_unlocked)
  {
    target.draw(m_number, states);
  }
  else
  {
    sf::Text num = m_number;
    sf::Color nc = num.getFillColor();
    nc.a = ui::LOCKED_ALPHA;
    num.setFillColor(nc);
    target.draw(num, states);
    target.draw(m_lock, states);
  }
}
