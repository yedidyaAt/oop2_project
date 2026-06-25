#include "LevelManager.h"

#include <utility>

#include "Collision.h"
#include "ParkingRules.h"
#include "SoundManager.h"
#include "Sounds.h"
#include "DisplaySettings.h"

LevelManager::LevelManager(sf::RenderWindow& window, LevelData levelData) :
  m_window(window),
  m_car(std::move(levelData.m_car)),
  m_target(std::move(levelData.m_target)),
  m_blocksObj(std::move(levelData.m_blocksObj)),
  m_decalsObj(std::move(levelData.m_decalsObj)),
  m_state(LevelState::Playing)
{
  buildView();
  m_timer.reset();
}

void LevelManager::buildView()
{
  m_worldView.setSize({ static_cast<float>(display::WINDOW_WIDTH),
                        static_cast<float>(display::WINDOW_HEIGHT) });
  m_worldView.setCenter({ static_cast<float>(display::WINDOW_WIDTH) / 2.f,
                          static_cast<float>(display::WINDOW_HEIGHT) / 2.f });
}

void LevelManager::handleEvent(const sf::Event& /*event*/)
{
  // Driving is polled in Car via the control strategy; nothing per-event here.
}

void LevelManager::update(sf::Time time)
{
  if (m_state != LevelState::Playing)
    return;

  m_timer.tick(time);
  m_car->update(time);

  checkConflict();
  checkParking();

  m_hud.setElapsed(m_timer.elapsedSeconds());
}

void LevelManager::checkConflict()
{
  for (const auto& obj : m_blocksObj)
  {
    if (collision::overlaps(m_car->getCorners(), obj->getCorners()))
    {
      SoundManager::getInstance().playEffectSound(Sounds::COLLISION);
      m_state = LevelState::Lost;   // any collision = immediate loss
      return;
    }
  }
}

void LevelManager::checkParking()
{
  if (m_car->isStand() && parkingRules::isParked(*m_car, *m_target))
  {
    SoundManager::getInstance().playEffectSound(Sounds::END_OF_STAGE);
    m_state = LevelState::Won;
  }
}

void LevelManager::draw()
{
  m_window.setView(m_worldView);

  for (const auto& obj : m_decalsObj)
    m_window.draw(*obj);
  for (const auto& obj : m_blocksObj)
    m_window.draw(*obj);
  m_window.draw(*m_target);
  m_window.draw(*m_car);

  // HUD in screen space
  m_window.setView(m_window.getDefaultView());
  m_hud.draw(m_window);
}

LevelState LevelManager::state() const { return m_state; }
float LevelManager::elapsedSeconds() const { return m_timer.elapsedSeconds(); }
