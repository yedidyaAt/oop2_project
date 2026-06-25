#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <optional>

#include "Button.h"
#include "StarRating.h"

// A modal panel drawn on top of a dimmed background. Holds a title, optional
// extra drawables (e.g. stars), and a vertical list of buttons. The owner adds
// buttons, then each frame calls updateHover() and, on a click, clickedIndex().
class Modal : public sf::Drawable
{
public:
  Modal(const std::string& title, sf::Vector2u windowSize);

  // Adds a button and returns its index (order added, top to bottom).
  std::size_t addButton(const std::string& label);

  // Extra text line shown under the title (e.g. "Time: 12.3s").
  void addInfoLine(const std::string& text);

  void updateHover(sf::Vector2f mousePos);

  // Returns the index of the button under the point, if any.
  std::optional<std::size_t> clickedIndex(sf::Vector2f point) const;

  void relayout(sf::Vector2u windowSize);

  void setStars(int stars);
protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  void rebuild();

  sf::RectangleShape                   m_dim;
  sf::RectangleShape                   m_panel;
  sf::Text                             m_title;
  std::vector<sf::Text>                m_infoLines;
  std::vector<std::unique_ptr<Button>> m_buttons;
  std::vector<std::string>             m_labels;
  sf::Vector2u                         m_winSize;
  int                                  m_stars = -1;   // -1 = no stars; 0..MAX = draw that many
  sf::Vector2f                         m_starsCenter;   // computed in rebuild(), used in draw()
};
