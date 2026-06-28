#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Animation.h"

class EffectManager
{
public:
  void add(std::unique_ptr<Animation> effect);
  void update(sf::Time time);
  void draw(sf::RenderWindow& window)const;


private:
  void deleteFinishedEffect();

  std::vector<std::unique_ptr<Animation>> m_effects;

};