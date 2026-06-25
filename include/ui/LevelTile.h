#pragma once

#include <SFML/Graphics.hpp>
#include <cstddef>

// A single level cube in the level-select grid. Shows the level number; if the
// level is locked it is dimmed and a lock icon is drawn over it. Only unlocked
// tiles react to hover.
class LevelTile : public sf::Drawable
{
public:
  LevelTile(std::size_t levelNumber, bool unlocked, sf::Vector2f center);

  void updateHover(sf::Vector2f mousePos);
  bool contains(sf::Vector2f point) const;
  bool isUnlocked() const;
  std::size_t levelNumber() const;

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  sf::RectangleShape m_box;
  sf::Text           m_number;
  sf::Sprite         m_lock;
  std::size_t        m_levelNumber;
  bool               m_unlocked;
  bool               m_hovered = false;
};
