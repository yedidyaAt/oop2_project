#include "Car.h"
#include "CarSettings.h"

#include <cmath>
#include <numbers>
#include <utility>
#include <iostream>

Car::Car(std::unique_ptr<ControlStrategy> control) :
  m_control(std::move(control)),
  m_rCar(sf::Vector2f({ 300.f,200.f })),
  m_whileR({ 50.f,20.f }),
  m_whileL({ 50.f,20.f }),
  m_angleWheel(0.f),
  m_heading(0.f),
  m_speed(0.f)
{
  this->setPosition({ 400.f,300.f });
  m_rCar.setFillColor(sf::Color::Blue);
  m_rCar.setOrigin({ 150.f,100.f });
  m_rCar.setPosition({ 0.f,0.f });

  m_whileL.setFillColor(sf::Color::Yellow);
  m_whileL.setOrigin({ 25.f,10.f });
  m_whileL.setPosition({ -120.f, 90.f });

  m_whileR.setFillColor(sf::Color::Yellow);
  m_whileR.setOrigin({ 25.f,10.f });
  m_whileR.setPosition({ -120.f,-90.f });
}

void Car::draw(sf::RenderTarget& window, sf::RenderStates state)const
{
  state.transform *= getTransform();

  window.draw(m_whileL, state);
  window.draw(m_whileR, state);
  window.draw(m_rCar, state);
}

void Car::update(float time)
{
  centerWheel(time);
  rotateLeft(time);
  rotateRight(time);
  rotateWheels();
  gas(time);
  reverse(time);
  brakes(time);
  gravitySlow(time);
  drive(time);
}

void Car::drive(float time)
{
  if (!m_speed)
    return;

  //(m_speed / car::CAR_MAX_SPEED) -> calculat the relative of speed using for how power the car turn
  // by his speed also giv info about dir if speed negative this (m_angleWheel - car::WHEEL_CENTER)
  // flip to (car::WHEEL_CENTER - m_angleWheel) and add to heading what we want if we goin back
  m_heading += (m_angleWheel - car::WHEEL_CENTER) * time * (m_speed / car::CAR_MAX_SPEED);

  float posX = m_speed * time * std::cos((std::numbers::pi / 180) * m_heading);
  float posY = m_speed * time * std::sin((std::numbers::pi / 180) * m_heading);

  this->move({ -posX,-posY });
  this->setRotation(sf::degrees(m_heading));
}

void Car::gas(float time)
{
  if (!m_control->wantsGas())
    return;

  m_speed += car::CAR_ACCELERATION * time;

  if (m_speed > car::CAR_MAX_SPEED)
    m_speed = car::CAR_MAX_SPEED;
}

void Car::reverse(float time)
{
  if (!m_control->wantsReverse())
    return;

  m_speed -= car::CAR_ACCELERATION * time;

  if (m_speed < -car::CAR_MAX_SPEED)
    m_speed = -car::CAR_MAX_SPEED;
}

void Car::rotateWheels()
{
  m_whileL.setRotation(sf::degrees(m_angleWheel));
  m_whileR.setRotation(sf::degrees(m_angleWheel));
}

void Car::brakes(float time)
{
  bool pressedSpace = m_control->wantsBrake() && m_speed != 0;
  bool pressedUpWhileSpeedDown = m_control->wantsGas() && m_speed < 0;
  bool pressedDownWhileSpeedUp = m_control->wantsReverse() && m_speed > 0;

  if (pressedSpace || pressedDownWhileSpeedUp || pressedUpWhileSpeedDown)
  {
    slowEngine(time, car::CAR_BRAKES);
  }
}

void Car::rotateRight(float time)
{
  if (!m_control->wantsRight())
    return;

  m_angleWheel += car::CAR_SPEED_ROTATE_WHEEL * time;

  if (m_angleWheel >= car::WHEEL_MAX_LEFT)
    m_angleWheel = car::WHEEL_MAX_LEFT;
}

void Car::rotateLeft(float time)
{
  if (!m_control->wantsLeft())
    return;

  m_angleWheel -= car::CAR_SPEED_ROTATE_WHEEL * time;

  if (m_angleWheel <= car::WHEEL_MAX_RIGHT)
    m_angleWheel = car::WHEEL_MAX_RIGHT;
}

void Car::gravitySlow(float time)
{
  if (m_control->wantsGas() || m_control->wantsReverse())
    return;

  slowEngine(time, car::CAR_GRAVITY);
}

void Car::slowEngine(float time, float slowBy)
{
  if (m_speed == 0)
    return;

  float gravityDir = m_speed / std::abs(m_speed);
  float speedDown = slowBy * time * gravityDir;

  //if my staps biger from what i have ubstract what left
  m_speed += (std::abs(m_speed) < std::abs(speedDown) ? -m_speed : -speedDown);
}

// bring the wheels slowly back to center when not steering
void Car::centerWheel(float time)
{
  if (!m_control->wantsGas() && !m_control->wantsReverse())
    return;

  if (m_control->wantsRight() || m_control->wantsLeft())
    return;

  float subtract = m_angleWheel - car::WHEEL_CENTER;

  if (std::abs(subtract) < car::WHEEL_SNAP)
    m_angleWheel = car::WHEEL_CENTER;
  else
    m_angleWheel += -subtract * car::CAR_SPEED_ROTATE_BODY * time;
}