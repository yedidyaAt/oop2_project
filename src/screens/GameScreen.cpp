#include "GameScreen.h"
#include "CreditsScreen.h"

#include "LevelBuilder.h"
#include "ResourceManager.h"
#include "Fonts.h"
#include "UISettings.h"
#include "DisplaySettings.h"
#include "SoundManager.h"
#include "Sounds.h"
#include "Musics.h"
#include "Progress.h"
#include "Score.h"

#include <sstream>
#include <iomanip>

namespace {
  constexpr float LOGICAL_W = static_cast<float>(display::WINDOW_WIDTH);

  std::string fmt(float seconds)
  {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << seconds << "s";
    return oss.str();
  }
}

GameScreen::GameScreen(sf::RenderWindow& window,
                       std::vector<std::string> playlist,
                       std::size_t levelIndex) :
  m_window(window),
  m_playlist(std::move(playlist)),
  m_levelIndex(levelIndex),
  m_level(window, LevelBuilder().buildLevel(m_playlist[levelIndex]))
{
  SoundManager::getInstance().playMusic(Musics::GAME);

  m_pauseBtn = std::make_unique<Button>("II  Pause",
    sf::Vector2f{ LOGICAL_W - 90.f, 32.f }, sf::Vector2f{ 150.f, 44.f });
}

void GameScreen::onResize(sf::Vector2u /*newSize*/){}

void GameScreen::openPauseModal()
{
  m_phase = Phase::Paused;
  m_modal = std::make_unique<Modal>("PAUSED", 
            sf::Vector2u{ display::WINDOW_WIDTH,display::WINDOW_HEIGHT });

  m_idxResume  = m_modal->addButton("Resume");
  m_idxRestart = m_modal->addButton("Restart Level");
  m_idxLevels  = m_modal->addButton("Level Select");
  m_idxMusic   = m_modal->addButton(m_musicMuted ? "Music: Off" : "Music: On");
}

void GameScreen::openWinModal()
{
  m_phase = Phase::Won;

  const float t = m_level.elapsedSeconds();
  Score score;
  score.compute(t, 0);

  // record + unlock next; find best (after recording)
  Progress::getInstance().recordCompletion(m_levelIndex, t);
  const auto best = Progress::getInstance().bestTime(m_levelIndex);

  m_modal = std::make_unique<Modal>("LEVEL COMPLETE!",
            sf::Vector2u{ display::WINDOW_WIDTH,display::WINDOW_HEIGHT });

  std::string timeLine = "Your time: " + fmt(t) +
                         (best.has_value() ? ("    |    Best: " + fmt(*best)) : "    |    Best: --");
  m_modal->addInfoLine(timeLine);
  m_modal->setStars(score.stars());   

  const bool lastLevel = (m_levelIndex + 1 >= m_playlist.size());
  if (!lastLevel)
    m_idxNext = m_modal->addButton("Next Level");
  else
    m_idxNext = m_modal->addButton("Finish (Credits)");

  m_idxReplay   = m_modal->addButton("Replay Level");
  m_idxToLevels = m_modal->addButton("Level Select");
}

void GameScreen::openLoseModal()
{
  m_phase = Phase::Lost;
  m_modal = std::make_unique<Modal>("CRASHED!",
            sf::Vector2u{ display::WINDOW_WIDTH,display::WINDOW_HEIGHT });

  m_idxReplay   = m_modal->addButton("Replay Level");
  m_idxToLevels = m_modal->addButton("Level Select");
}

void GameScreen::goToLevel(std::size_t index)
{
  m_next = std::make_unique<GameScreen>(m_window, m_playlist, index);
  m_action = ScreenAction::Replace;   
}

void GameScreen::goToLevelSelectPop()
{
  // GameScreen was pushed on top of LevelSelect, so popping returns there.
  m_action = ScreenAction::Pop;
}

void GameScreen::goToCredits()
{
  m_next = std::make_unique<CreditsScreen>(m_window, true);
  m_action = ScreenAction::Replace;
}

void GameScreen::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
  if (event.is<sf::Event::Closed>())
  {
    m_action = ScreenAction::Quit;
    return;
  }

  const sf::Vector2f mouse =
    window.mapPixelToCoords(sf::Mouse::getPosition(window));

  // ----- modal phases -----
  if (m_phase != Phase::Playing)
  {
    if (event.getIf<sf::Event::MouseMoved>() && m_modal)
      m_modal->updateHover(mouse);

    if (const auto* mb = event.getIf<sf::Event::MouseButtonPressed>())
      if (mb->button == sf::Mouse::Button::Left)
        handleModalClick(mouse);

    // Esc resumes from pause
    if (const auto* key = event.getIf<sf::Event::KeyPressed>())
      if (key->code == sf::Keyboard::Key::Escape && m_phase == Phase::Paused)
      {
        m_phase = Phase::Playing;
        m_modal.reset();
      }
    return;
  }

  // ----- playing phase -----
  if (event.getIf<sf::Event::MouseMoved>())
    m_pauseBtn->updateHover(mouse);

  if (const auto* mb = event.getIf<sf::Event::MouseButtonPressed>())
    if (mb->button == sf::Mouse::Button::Left && m_pauseBtn->contains(mouse))
    {
      SoundManager::getInstance().playEffectSound(Sounds::CLICKING_BUTTON);
      openPauseModal();
    }

  if (const auto* key = event.getIf<sf::Event::KeyPressed>())
    if (key->code == sf::Keyboard::Key::Escape)
      openPauseModal();

  m_level.handleEvent(event);
}

void GameScreen::handleModalClick(sf::Vector2f mouse)
{
  if (!m_modal)
    return;

  const auto clicked = m_modal->clickedIndex(mouse);
  if (!clicked.has_value())
    return;

  const std::size_t i = *clicked;
  SoundManager::getInstance().playEffectSound(Sounds::CLICKING_BUTTON);

  if (m_phase == Phase::Paused)
  {
    if (i == m_idxResume)
    {
      m_phase = Phase::Playing;
      m_modal.reset();
    }
    else if (i == m_idxRestart)
    {
      goToLevel(m_levelIndex);
    }
    else if (i == m_idxLevels)
    {
      goToLevelSelectPop();
    }
    else if (i == m_idxMusic)
    {
      m_musicMuted = !m_musicMuted;
      if (m_musicMuted) SoundManager::getInstance().pauseMusic();
      else              SoundManager::getInstance().resumeMusic();
      // refresh label
      openPauseModal();
    }
  }
  else if (m_phase == Phase::Won)
  {
    if (i == m_idxNext)
    {
      const bool lastLevel = (m_levelIndex + 1 >= m_playlist.size());
      if (lastLevel) goToCredits();
      else           goToLevel(m_levelIndex + 1);
    }
    else if (i == m_idxReplay)   goToLevel(m_levelIndex);
    else if (i == m_idxToLevels) goToLevelSelectPop();
  }
  else if (m_phase == Phase::Lost)
  {
    if (i == m_idxReplay)        goToLevel(m_levelIndex);
    else if (i == m_idxToLevels) goToLevelSelectPop();
  }
}

void GameScreen::update(sf::Time dt)
{
  if (m_phase != Phase::Playing)
    return;

  m_level.update(dt);

  if (m_level.state() == LevelState::Won)
    openWinModal();
  else if (m_level.state() == LevelState::Lost)
    openLoseModal();
}

void GameScreen::draw(sf::RenderWindow& window)
{
  // world + HUD always drawn (modal dims it for the "blurred behind" look)
  m_level.draw();

  if (m_phase == Phase::Playing)
  {
    window.setView(window.getDefaultView());
    window.draw(*m_pauseBtn);
  }
  else if (m_modal)
  {
    window.setView(window.getDefaultView());
    window.draw(*m_modal);
 
  }
}

ScreenAction GameScreen::action() const { return m_action; }
std::unique_ptr<Screen> GameScreen::takeNext() { return std::move(m_next); }
