#include "Modal.h"

#include "ResourceManager.h"
#include "Fonts.h"
#include "UISettings.h"

Modal::Modal(const std::string& title, sf::Vector2u windowSize) :
  m_title(ResourceManager::getInstance().getFont(Fonts::MAIN)),
  m_winSize(windowSize)
{
  m_title.setString(title);
  m_title.setCharacterSize(ui::HEADING_SIZE);
  m_title.setFillColor(ui::TITLE_COL);
  m_title.setOutlineColor(ui::OUTLINE_COL);
  m_title.setOutlineThickness(ui::TITLE_OUTLINE);

  rebuild();
}

std::size_t Modal::addButton(const std::string& label)
{
  m_labels.push_back(label);
  rebuild();
  return m_labels.size() - 1;
}

void Modal::addInfoLine(const std::string& text)
{
  sf::Text line(ResourceManager::getInstance().getFont(Fonts::MAIN));
  line.setString(text);
  line.setCharacterSize(ui::BODY_SIZE);
  line.setFillColor(ui::BODY_COL);
  m_infoLines.push_back(line);
  rebuild();
}

void Modal::relayout(sf::Vector2u windowSize)
{
  m_winSize = windowSize;
  rebuild();
}

void Modal::setStars(int stars)
{
  m_stars = stars;
  rebuild();
}

void Modal::rebuild()
{
  const sf::Vector2f winF{ static_cast<float>(m_winSize.x), static_cast<float>(m_winSize.y) };
  const sf::Vector2f center{ winF.x / 2.f, winF.y / 2.f };

  // dim layer covers whole window
  m_dim.setSize(winF);
  m_dim.setPosition({ 0.f, 0.f });
  m_dim.setFillColor(ui::MODAL_DIM);

  // panel
  m_panel.setSize({ ui::MODAL_PANEL_W, ui::MODAL_PANEL_H });
  m_panel.setOrigin({ ui::MODAL_PANEL_W / 2.f, ui::MODAL_PANEL_H / 2.f });
  m_panel.setPosition(center);
  m_panel.setFillColor(ui::MODAL_PANEL);
  m_panel.setOutlineThickness(ui::MODAL_OUTLINE_T);
  m_panel.setOutlineColor(ui::MODAL_OUTLINE);

  const float panelTop = center.y - ui::MODAL_PANEL_H / 2.f;
  const float panelBot = center.y + ui::MODAL_PANEL_H / 2.f;

  // a cursor that walks DOWN the panel; each element sits below the previous
  float cursorY = panelTop + ui::MODAL_PADDING;

  // ----- stars row (top) -----
  if (m_stars >= 0)
  {
    m_starsCenter = { center.x, cursorY + ui::STAR_SIZE / 2.f };
    cursorY += ui::STAR_SIZE + 18.f;
  }

  // ----- title -----
  {
    auto b = m_title.getLocalBounds();
    m_title.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
    m_title.setPosition({ center.x, cursorY + ui::HEADING_SIZE / 2.f });
    cursorY += ui::HEADING_SIZE + 24.f;
  }

  // ----- info lines -----
  for (auto& line : m_infoLines)
  {
    auto b = line.getLocalBounds();
    line.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
    line.setPosition({ center.x, cursorY + ui::BODY_SIZE / 2.f });
    cursorY += ui::BODY_SIZE + 10.f;
  }

  // ----- buttons (stacked from the bottom up) -----
  m_buttons.clear();
  const std::size_t n = m_labels.size();
  const float stackH = n * ui::BTN_HEIGHT + (n > 0 ? (n - 1) * ui::BTN_SPACING : 0.f);
  float by = panelBot - ui::MODAL_PADDING - stackH + ui::BTN_HEIGHT / 2.f;
  for (std::size_t i = 0; i < n; ++i)
  {
    m_buttons.push_back(std::make_unique<Button>(
      m_labels[i],
      sf::Vector2f{ center.x, by },
      sf::Vector2f{ ui::BTN_WIDTH, ui::BTN_HEIGHT }));
    by += ui::BTN_HEIGHT + ui::BTN_SPACING;
  }
}

void Modal::updateHover(sf::Vector2f mousePos)
{
  for (auto& b : m_buttons)
    b->updateHover(mousePos);
}

std::optional<std::size_t> Modal::clickedIndex(sf::Vector2f point) const
{
  for (std::size_t i = 0; i < m_buttons.size(); ++i)
    if (m_buttons[i]->contains(point))
      return i;
  return std::nullopt;
}

void Modal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_dim, states);
  target.draw(m_panel, states);
  target.draw(m_title, states);
  for (const auto& line : m_infoLines)
    target.draw(line, states);

  if (m_stars >= 0)
  {
    StarRating stars(m_stars, m_starsCenter);
    target.draw(stars, states);
  }

  for (const auto& b : m_buttons)
    target.draw(*b, states);
}
