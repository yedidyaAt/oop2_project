#include "AIStrategy.h"

bool AIStrategy::wantsGas()
{
  return true;
}

bool AIStrategy::wantsReverse()
{
  return false;
}

bool AIStrategy::wantsLeft()
{
  return false;
}

bool AIStrategy::wantsRight()
{
  return true;
}

bool AIStrategy::wantsBrake()
{
  return false;
}
