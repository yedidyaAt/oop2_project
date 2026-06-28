#include "Button.h"

#include "ResourceManager.h"
#include "Fonts.h"
#include "UISettings.h"

Button::Button(const std::string& label, sf::Vector2f center, sf::Vector2f size) :
  m_label(ResourceManager::getInstance().getFont(fonts::MAIN)),
  m_center(center),
  m_size(size)
{
  m_label.setString(label);
  m_label.setCharacterSize(ui::BUTTON_SIZE);

  m_box.setOutlineThickness(ui::BTN_OUTLINE);
  m_box.setOutlineColor(ui::BTN_OUTLINE_COL);

  layout();
}

void Button::setCenter(sf::Vector2f center)
{
  m_center = center;
  layout();
}

void Button::setSize(sf::Vector2f size)
{
  m_size = size;
  layout();
}

void Button::layout()
{
  // measure the label first
  auto b = m_label.getLocalBounds();
  const float textWidth = b.size.x;

  // make sure the box is at least wide enough for the text + padding
  float boxWidth = m_size.x;
  const float needed = textWidth + 2.f * ui::BTN_CORNER_PAD;
  if (needed > boxWidth)
    boxWidth = needed;

  const sf::Vector2f boxSize{ boxWidth, m_size.y };

  m_box.setSize(boxSize);
  m_box.setOrigin(boxSize / 2.f);
  m_box.setPosition(m_center);

  m_label.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
  m_label.setPosition(m_center);
}

void Button::updateHover(sf::Vector2f mousePos)
{
  m_hovered = contains(mousePos);
}

bool Button::contains(sf::Vector2f point) const
{
  return m_box.getGlobalBounds().contains(point);
}

bool Button::isHovered() const
{
  return m_hovered;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  sf::RectangleShape box = m_box;
  box.setFillColor(m_hovered ? ui::BTN_FILL_HOVER : ui::BTN_FILL);

  sf::Text label = m_label;
  label.setFillColor(m_hovered ? ui::BTN_TEXT_HOVER : ui::BTN_TEXT);

  target.draw(box, states);
  target.draw(label, states);
}
