#include "SmokeAnimation.h"

#include <memory>

#include "SmokeAniSettings.h"
#include "Effects.h"
#include "ResourceManager.h"


SmokeAnimation::SmokeAnimation(const sf::Texture& textur,
                               const sf::Vector2f& pos,
                               bool loop) :

  Animation(smokeCfg::FRAMES, smokeCfg::MOVE_FRAME,loop),
  m_spriteSheet(textur)
{
  m_spriteSheet.setPosition(pos);
  
  sf::IntRect frame = currentFrame();
  sf::Vector2f centerFrame = { frame.size.x / 2.f,frame.size.y / 2.f };
  m_spriteSheet.setOrigin(centerFrame);
  m_spriteSheet.setTextureRect(currentFrame());
}

void SmokeAnimation::onMoveFrame()
{
  sf::IntRect frame = currentFrame();
  sf::Vector2f centerFrame = { frame.size.x / 2.f,frame.size.y / 2.f };
  m_spriteSheet.setOrigin(centerFrame);
  m_spriteSheet.setTextureRect(currentFrame());
  m_spriteSheet.setScale({ smokeCfg::SCALE, smokeCfg::SCALE });
}

bool SmokeAnimation::isFinished() const
{
  return m_finished;
}

void SmokeAnimation::draw(sf::RenderWindow& window) const
{
  window.draw(m_spriteSheet);
}
