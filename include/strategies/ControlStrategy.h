#pragma once

class ControlStrategy
{
public:
  virtual ~ControlStrategy() = default;
  virtual bool wantsGas() = 0;
  virtual bool wantsReverse() = 0;
  virtual bool wantsLeft() = 0;
  virtual bool wantsRight() = 0;
  virtual bool wantsBrake() = 0;
};
