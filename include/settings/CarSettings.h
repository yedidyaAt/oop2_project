#pragma once

namespace car
{
  // driving speed in pixels per second
  constexpr float CAR_SPEED_DRIVE = 250.f;
  constexpr float CAR_ACCELERATION = 100.f;
  constexpr float CAR_MAX_SPEED = 300.f;
  constexpr float CAR_GRAVITY = 10.f;
  constexpr float CAR_BRAKES = 200.f;

  constexpr float OFFEST_WHEEL_X = 0.6f;
  constexpr float OFFEST_WHEEL_Y = 0.75f;


  // how fast the wheels turn (degrees per second)
  constexpr float CAR_SPEED_ROTATE_WHEEL = 120.f;

  // how fast the car body turns while driving
  constexpr float CAR_SPEED_ROTATE_BODY = 3.5f;

  // wheel angle when going straight
  constexpr float WHEEL_CENTER = 0.f;

  // how far the wheels can turn to each side
  constexpr float WHEEL_MAX_LEFT = 50.f;
  constexpr float WHEEL_MAX_RIGHT = -50.f;

  // if the wheel is this close to center, snap it to center
  constexpr float WHEEL_SNAP = 0.9f;
}