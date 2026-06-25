#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

// A self-contained clickable button: a filled rounded-ish rectangle with a
// centered text label. Knows how to highlight on hover and report clicks.
class Button : public sf::Drawable
{
public:
  Button(const std::string& label, sf::Vector2f center, sf::Vector2f size);

  void setCenter(sf::Vector2f center);
  void setSize(sf::Vector2f size);

  // Update hover state from the current mouse position (in world coords).
  void updateHover(sf::Vector2f mousePos);

  bool contains(sf::Vector2f point) const;
  bool isHovered() const;

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  void layout();

  sf::RectangleShape m_box;
  sf::Text           m_label;
  sf::Vector2f       m_center;
  sf::Vector2f       m_size;
  bool               m_hovered = false;
};
