#pragma once

#include <SFML/Graphics.hpp>

#include "ControlStrategy.h"

class KeyboardStrategy: public ControlStrategy
{
public:
  ~KeyboardStrategy() override = default;
  bool wantsGas() override;
  bool wantsReverse() override;
  bool wantsLeft() override;
  bool wantsRight() override;
  bool wantsBrake() override;

};
