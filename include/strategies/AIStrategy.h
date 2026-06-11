#pragma once

#include "ControlStrategy.h"

class AIStrategy : public ControlStrategy
{
public:
  ~AIStrategy() override = default;
  bool wantsGas() override;
  bool wantsReverse() override;
  bool wantsLeft() override;
  bool wantsRight() override;
  bool wantsBrake() override;
};