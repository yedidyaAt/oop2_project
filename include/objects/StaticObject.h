#pragma once

#include "GameObject.h"

class StaticObject : public GameObject
{
public:
  StaticObject(const sf::Texture& texture, const sf::Vector2f& pos,
                                    float fitSize,sf::Angle angle);

  void update(sf::Time time)override;

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates state)const override;

private:
};