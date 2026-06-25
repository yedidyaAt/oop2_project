#pragma once

#include "GameObject.h"

class StaticObject : public GameObject
{
public:
  StaticObject(const sf::Texture& texture, const sf::Vector2f& pos,
                                    float fitSize,sf::Angle angle,
                                    bool block);

  void update(sf::Time time)override;
  sf::FloatRect getGlobalBounds() const override;

  std::array<sf::Vector2f, 4> getCorners() const override;
  sf::Angle getAngle()const override;


protected:
  void draw(sf::RenderTarget& target, sf::RenderStates state)const override;

private:
};
