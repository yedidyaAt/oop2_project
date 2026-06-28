#include "Animation.h"

Animation::Animation(const std::vector<sf::IntRect>& frames, float moveFrame,bool loop) :
  m_frames(frames),
  m_moveFrame(moveFrame),
  m_timer(0.f),
  m_indxFrame(0),
  m_finished(false),
  m_loop(loop)
{
}

void Animation::update(sf::Time time)
{
  updateTimer(time.asSeconds());
  if (isTimeMoveFrame())
  {
    m_timer = 0.f;
    updateIndx();
    onMoveFrame();
  }
}

void Animation::onMoveFrame()
{
}

sf::IntRect Animation::currentFrame() const
{
  return m_frames[m_indxFrame];
}

void Animation::updateTimer(float dt)
{
  m_timer += dt;
}

bool Animation::isTimeMoveFrame() const
{
  return m_timer >= m_moveFrame;
}

void Animation::updateIndx()
{
  m_indxFrame++;
  if (m_indxFrame >= static_cast<int>(m_frames.size()))
  {
    if (m_loop)
    {
      m_indxFrame = 0;                              // loop: back to start
    }
    else
    {
      m_indxFrame = static_cast<int>(m_frames.size()) - 1;  // stay on last valid frame
      m_finished = true;                            // mark done
    }
  }
}