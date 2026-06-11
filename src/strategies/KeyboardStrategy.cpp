#include "KeyboardStrategy.h"


bool KeyboardStrategy::wantsGas()
{
  return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
}

bool KeyboardStrategy::wantsReverse()
{
  return  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
}

bool KeyboardStrategy::wantsLeft()
{
  return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
}

bool KeyboardStrategy::wantsRight()
{
  return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
}

bool KeyboardStrategy::wantsBrake()
{
  return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
}
