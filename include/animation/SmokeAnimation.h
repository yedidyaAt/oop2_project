#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"

class SmokeAnimation: public Animation
{
 public:
   SmokeAnimation(const sf::Texture& textur, const sf::Vector2f& pos,bool loop);

   void draw(sf::RenderWindow& window)const override;
   void onMoveFrame() override;

   bool isFinished() const override;
private:
  sf::Sprite m_spriteSheet;
};