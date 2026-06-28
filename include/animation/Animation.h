#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Base: the pure timing mechanism. Knows frames, current index, and timing.
// Does NOT know about sprites or drawing — that belongs to derived classes.
class Animation
{
public:
  Animation(const std::vector<sf::IntRect>& frames, float moveFrame,bool loop);
  virtual ~Animation() = default;

  // advance time; if enough passed, move to next frame
  virtual void update(sf::Time time);
  virtual void draw(sf::RenderWindow& window)const = 0;

  // the inhreate deisde what to do when is Time to move fram
  virtual void onMoveFrame();

  // the source rect for the frame shown right now
  sf::IntRect currentFrame() const;

  virtual bool isFinished()const = 0;
protected:
  void updateTimer(float dt);
  bool isTimeMoveFrame() const;
  void updateIndx();

  std::vector<sf::IntRect> m_frames;
  float                    m_moveFrame;
  float                    m_timer;
  int                      m_indxFrame;
  bool                     m_loop;
  bool                     m_finished;
};