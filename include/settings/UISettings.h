#pragma once

#include <SFML/Graphics/Color.hpp>

// All UI geometry, colors and timings live here. No magic numbers in widgets.
namespace ui
{
  // ----- character sizes -----
  constexpr unsigned TITLE_SIZE   = 56;
  constexpr unsigned HEADING_SIZE = 40;
  constexpr unsigned BUTTON_SIZE  = 26;
  constexpr unsigned BODY_SIZE    = 22;
  constexpr unsigned SMALL_SIZE   = 18;

  // ----- buttons -----
  constexpr float BTN_WIDTH        = 320.f;
  constexpr float BTN_HEIGHT       = 60.f;
  constexpr float BTN_SPACING      = 18.f;   // vertical gap between stacked buttons
  constexpr float BTN_OUTLINE      = 2.f;
  constexpr float BTN_CORNER_PAD   = 6.f;    // text inset feel

  // button colors
  inline const sf::Color BTN_FILL        {30, 30, 40, 220};
  inline const sf::Color BTN_FILL_HOVER  {70, 110, 180, 240};
  inline const sf::Color BTN_OUTLINE_COL {220, 220, 230};
  inline const sf::Color BTN_TEXT        {240, 240, 245};
  inline const sf::Color BTN_TEXT_HOVER  {255, 255, 255};

  // ----- text colors -----
  inline const sf::Color TITLE_COL   {255, 255, 255};
  inline const sf::Color OUTLINE_COL {0, 0, 0};
  inline const sf::Color BODY_COL    {235, 235, 240};
  inline const sf::Color DIM_COL     {200, 200, 205};
  constexpr float        TITLE_OUTLINE = 3.f;

  // ----- level select grid -----
  constexpr int   GRID_COLS      = 3;
  constexpr float TILE_SIZE      = 140.f;
  constexpr float TILE_GAP       = 28.f;
  constexpr float TILE_OUTLINE   = 3.f;
  inline const sf::Color TILE_UNLOCKED      {60, 120, 90, 235};
  inline const sf::Color TILE_UNLOCKED_HOV  {90, 170, 120, 255};
  inline const sf::Color TILE_LOCKED        {50, 50, 55, 235};
  inline const sf::Color TILE_OUTLINE_COL   {230, 230, 235};
  inline const sf::Color TILE_NUM_COL       {255, 255, 255};
  constexpr std::uint8_t LOCKED_ALPHA       = 90;   // slight transparency on locked tiles

  // ----- modal (popup) -----
  inline const sf::Color MODAL_DIM    {0, 0, 0, 150};   // dim layer over the blurred level
  inline const sf::Color MODAL_PANEL  {25, 28, 38, 245};
  inline const sf::Color MODAL_OUTLINE{220, 220, 230};
  constexpr float MODAL_PANEL_W   = 520.f;
  constexpr float MODAL_PANEL_H   = 480.f;
  constexpr float MODAL_OUTLINE_T = 2.f;
  constexpr float MODAL_PADDING   = 30.f;

  // ----- HUD stopwatch widget -----
  constexpr float CLOCK_RADIUS   = 22.f;
  constexpr float CLOCK_X        = 38.f;   // center
  constexpr float CLOCK_Y        = 38.f;
  constexpr float CLOCK_HAND_LEN = 16.f;
  constexpr float CLOCK_OUTLINE  = 3.f;
  inline const sf::Color CLOCK_FACE    {245, 245, 245, 230};
  inline const sf::Color CLOCK_RIM     {30, 30, 30};
  inline const sf::Color CLOCK_HAND    {200, 40, 40};
  inline const sf::Color CLOCK_TEXT    {255, 255, 255};
  // the hand sweeps a full circle every CLOCK_SWEEP_SECONDS
  constexpr float CLOCK_SWEEP_SECONDS = 60.f;

  // ----- win screen stars -----
  constexpr int   MAX_STARS   = 3;
  constexpr float STAR_SIZE   = 56.f;
  constexpr float STAR_GAP    = 14.f;

  // ----- credits scroll -----
  constexpr float CREDITS_SCROLL_SPEED = 60.f;  // pixels per second, upward
  constexpr float CREDITS_LINE_GAP     = 14.f;
}
