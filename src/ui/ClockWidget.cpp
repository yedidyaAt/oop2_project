#include "ClockWidget.h"

#include "ResourceManager.h"
#include "Fonts.h"
#include "UISettings.h"

#include <cmath>
#include <numbers>
#include <sstream>
#include <iomanip>

ClockWidget::ClockWidget() :
  m_text(ResourceManager::getInstance().getFont(fonts::MAIN))
{
  m_face.setRadius(ui::CLOCK_RADIUS);
  m_face.setOrigin({ ui::CLOCK_RADIUS, ui::CLOCK_RADIUS });
  m_face.setPosition({ ui::CLOCK_X, ui::CLOCK_Y });
  m_face.setFillColor(ui::CLOCK_FACE);
  m_face.setOutlineThickness(ui::CLOCK_OUTLINE);
  m_face.setOutlineColor(ui::CLOCK_RIM);

  float knobR = ui::CLOCK_RADIUS * 0.22f;
  m_knob.setRadius(knobR);
  m_knob.setOrigin({ knobR, knobR });
  m_knob.setPosition({ ui::CLOCK_X, ui::CLOCK_Y - ui::CLOCK_RADIUS - ui::CLOCK_OUTLINE });
  m_knob.setFillColor(ui::CLOCK_RIM);

  m_hand.setSize({ 2.5f, ui::CLOCK_HAND_LEN });
  m_hand.setOrigin({ 1.25f, ui::CLOCK_HAND_LEN }); // pivot at bottom
  m_hand.setPosition({ ui::CLOCK_X, ui::CLOCK_Y });
  m_hand.setFillColor(ui::CLOCK_HAND);

  m_text.setCharacterSize(ui::BODY_SIZE);
  m_text.setFillColor(ui::CLOCK_TEXT);
  m_text.setOutlineColor(ui::OUTLINE_COL);
  m_text.setOutlineThickness(2.f);
  m_text.setPosition({ ui::CLOCK_X + ui::CLOCK_RADIUS + 14.f, ui::CLOCK_Y - ui::CLOCK_RADIUS * 0.6f });
}

void ClockWidget::setElapsed(float seconds)
{
  m_elapsed = seconds;

  float fraction = std::fmod(seconds, ui::CLOCK_SWEEP_SECONDS) / ui::CLOCK_SWEEP_SECONDS;
  m_hand.setRotation(sf::degrees(fraction * 360.f));

  std::ostringstream oss;
  oss << std::fixed << std::setprecision(1) << seconds << "s";
  m_text.setString(oss.str());
}

void ClockWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_knob, states);
  target.draw(m_face, states);
  target.draw(m_hand, states);
  target.draw(m_text, states);
}
