#pragma once

#include "GameObject.h"

class Wall : public GameObject
{
public:
  Wall(const sf::Vector2f& pos);

  void update(sf::Time time)override;

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates state)const override;

private:
};