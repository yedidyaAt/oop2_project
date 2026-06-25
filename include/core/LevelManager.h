#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "GameObject.h"
#include "LevelData.h"
#include "LevelState.h"
#include "HUD.h"
#include "Timer.h"

// Runs ONE level. Driven by GameScreen (handleEvent / update / draw); it does
// not own the main loop and does not draw win/lose UI - that is the screen's
// job (via modals). A collision is an immediate loss.
class LevelManager
{
public:
  LevelManager(sf::RenderWindow& window, LevelData levelData);

  void handleEvent(const sf::Event& event);
  void update(sf::Time time);
  void draw();           // draws world + HUD (no popups)

  LevelState state() const;
  float      elapsedSeconds() const;

private:
  void checkConflict();
  void checkParking();
  void buildView();

  sf::RenderWindow&                        m_window;
  std::unique_ptr<Car>                     m_car        = std::unique_ptr<Car>();
  std::unique_ptr<GameObject>              m_target     = std::unique_ptr<GameObject>();
  std::vector<std::unique_ptr<GameObject>> m_blocksObj  = std::vector<std::unique_ptr<GameObject>>();
  std::vector<std::unique_ptr<GameObject>> m_decalsObj  = std::vector<std::unique_ptr<GameObject>>();
  LevelState                               m_state;

  sf::View                                 m_worldView;
  HUD                                      m_hud;
  Timer                                    m_timer;
};
