#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Animation.h"

// Free functions that build ready-to-use effects.
// Each knows which concrete type + texture to use; callers just say "make X here".
// To add a new effect: add one function here + its #include in the .cpp.
namespace effectMaker
{
  std::unique_ptr<Animation> makeSmokeLoop(sf::Vector2f pos);
}