#pragma once

#include "Screen.h"
#include "core/LevelManager.h"
#include "ui/Button.h"
#include "ui/Modal.h"


#include <string>
#include <vector>
#include <memory>
#include <cstddef>

class GameScreen : public Screen
{
public:
  GameScreen(sf::RenderWindow& window,
             std::vector<std::string> playlist,
             std::size_t levelIndex);

  void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
  void update(sf::Time dt) override;
  void draw(sf::RenderWindow& window) override;
  void onResize(sf::Vector2u newSize) override;

  ScreenAction action() const override;
  std::unique_ptr<Screen> takeNext() override;

private:
  enum class Phase { Playing, Paused, Won, Lost };

  void openPauseModal();
  void openWinModal();
  void openLoseModal();
  void handleModalClick(sf::Vector2f mouse);

  void goToLevel(std::size_t index);     // replace with a fresh GameScreen
  void goToLevelSelectPop();             // pop back to level select
  void goToCredits();                    // game complete

  sf::RenderWindow&        m_window;
  std::vector<std::string> m_playlist;
  std::size_t              m_levelIndex;

  LevelManager             m_level;
  std::unique_ptr<Button>  m_pauseBtn;

  Phase                    m_phase = Phase::Playing;
  std::unique_ptr<Modal>   m_modal;

  // indices of buttons inside the current modal
  std::size_t m_idxResume = 0, m_idxRestart = 0, m_idxLevels = 0, m_idxMusic = 0;
  std::size_t m_idxNext = 0, m_idxReplay = 0, m_idxToLevels = 0;
  bool        m_musicMuted = false;

  ScreenAction            m_action = ScreenAction::None;
  std::unique_ptr<Screen> m_next;
};
