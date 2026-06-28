#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace smokeCfg
{
  constexpr float MOVE_FRAME = 0.1f;
  constexpr float SCALE = 3.f;

  inline const std::vector<sf::IntRect> FRAMES = {
      sf::IntRect({ 150, 160 }, { 39, 39 }),
      sf::IntRect({ 190, 160 }, { 42, 39 }),
      sf::IntRect({ 233, 160 }, { 45, 39 }),
      sf::IntRect({ 119, 164 }, { 30, 32 }),
      sf::IntRect({  94, 167 }, { 24, 26 }),
      sf::IntRect({  73, 170 }, { 20, 20 }),
      sf::IntRect({  56, 173 }, { 16, 15 }),
      sf::IntRect({  20, 175 }, { 11, 12 }),
      sf::IntRect({  33, 175 }, { 10, 12 }),
      sf::IntRect({  44, 175 }, { 11, 12 }),
  };
}