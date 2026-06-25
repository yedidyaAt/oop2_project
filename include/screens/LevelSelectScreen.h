#pragma once

#include "Screen.h"
#include "ui/Button.h"
#include "ui/Background.h"
#include "ui/LevelTile.h"

#include <vector>
#include <string>
#include <memory>

class LevelSelectScreen : public Screen
{
public:
  LevelSelectScreen(sf::RenderWindow& window, std::vector<std::string> playlist);

  void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
  void update(sf::Time dt) override;
  void draw(sf::RenderWindow& window) override;
  void onResize(sf::Vector2u newSize) override;
  void onResume() override;


  ScreenAction action() const override;
  std::unique_ptr<Screen> takeNext() override;

private:
  void build();
  void layout();

  sf::RenderWindow&        m_window;
  std::vector<std::string> m_playlist;
  Background               m_bg;
  sf::Text                 m_title;
  std::vector<std::unique_ptr<LevelTile>> m_tiles;
  std::unique_ptr<Button>  m_back;
  std::unique_ptr<Button>  m_reset;
  ScreenAction             m_action = ScreenAction::None;
  std::unique_ptr<Screen>  m_next;
};
