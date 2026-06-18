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
  return true;
}

bool AIStrategy::wantsRight()
{
  return false;
}

bool AIStrategy::wantsBrake()
{
  return false;
}
