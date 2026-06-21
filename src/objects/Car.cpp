#include "Car.h"
#include "CarSettings.h"

#include "Factory.h"
#include "Objects.h"
#include "ObjectDescriptor.h"
#include "StaticObject.h"
#include "ResourceManager.h"
#include "ObjectSizes.h"
#include "KeyboardStrategy.h"
#include "SpriteUtils.h"
#include "Collision.h"

#include <cmath>
#include <numbers>
#include <utility>
#include <iostream>



// ======== register =========
static bool registery = factory::registerCreator(Objects::PLAYER_CAR,
  [](const ObjectDescriptor& objDes)
  {
    return std::make_unique<Car>(
      ResourceManager::getInstance().getTexture(Objects::PLAYER_CAR),
      sf::Vector2f{ objDes.m_x, objDes.m_y },
      objectSizes::playerCar::WIDTH,
      sf::degrees(objDes.m_angle),
      std::make_unique<KeyboardStrategy>());
  }
);


Car::Car(const sf::Texture& texture,
         const sf::Vector2f& pos,
         float fitSize,
         sf::Angle angle,
         std::unique_ptr<ControlStrategy> control):
 
  GameObject(texture,sf::Vector2f{}, true), // vec2F{} becouse we live at transform world
  m_control(std::move(control)),
  m_whileR(ResourceManager::getInstance().getTexture(Objects::WHEEL)),
  m_whileL(ResourceManager::getInstance().getTexture(Objects::WHEEL)),
  m_angleWheel(0.f),
  m_heading(angle.asDegrees()),
  m_speed(0.f)
{
  this->setRotation(angle);
  this->setPosition(pos);

  spriteUtils::fitToSize(m_sprite, fitSize);
  m_sprite.setOrigin(m_sprite.getLocalBounds().size/2.f);
  m_sprite.setPosition({ 0.f,0.f });

  sf::Vector2f halfBody{
     m_sprite.getLocalBounds().size.x / 2.f * m_sprite.getScale().x,
     m_sprite.getLocalBounds().size.y / 2.f * m_sprite.getScale().y
  };

  spriteUtils::fitToSize(m_whileL, objectSizes::wheel::WIDTH);
  m_whileL.setOrigin(m_whileL.getLocalBounds().size / 2.f);
  m_whileL.setPosition({ -halfBody.x*car::OFFEST_WHEEL_X,
                          halfBody.y* car::OFFEST_WHEEL_Y});

  spriteUtils::fitToSize(m_whileR, objectSizes::wheel::WIDTH);
  m_whileR.setOrigin(m_whileR.getLocalBounds().size / 2.f);
  m_whileR.setPosition({ -halfBody.x* car::OFFEST_WHEEL_X,
                         -halfBody.y* car::OFFEST_WHEEL_Y });
}

void Car::draw(sf::RenderTarget& window, sf::RenderStates state)const
{
  state.transform *= getTransform();

  window.draw(m_whileL, state);
  window.draw(m_whileR, state);
  window.draw(m_sprite, state);
}

void Car::update(sf::Time time)
{
  centerWheel(time.asSeconds());
  rotateLeft(time.asSeconds());
  rotateRight(time.asSeconds());
  rotateWheels();
  gas(time.asSeconds());
  reverse(time.asSeconds());
  brakes(time.asSeconds());
  gravitySlow(time.asSeconds());
  drive(time.asSeconds());
}

sf::FloatRect Car::getGlobalBounds() const
{
  sf::Transform combined =getTransform()* m_sprite.getTransform();
  return combined.transformRect(m_sprite.getLocalBounds());
}

std::array<sf::Vector2f, 4> Car::getCorners() const
{
  sf::Transform combined = getTransform() * m_sprite.getTransform();
  return collision::getGlobalePoints(m_sprite.getLocalBounds(),combined);
}

void Car::drive(float time)
{
  if (!m_speed)
    return;

  sf::Vector2f halfBody{
     m_sprite.getLocalBounds().size.x / 2.f * m_sprite.getScale().x,
     m_sprite.getLocalBounds().size.y / 2.f * m_sprite.getScale().y
  };

  // use old heading
  sf::Vector2f taileCar = {
    getPosition().x + halfBody.x * static_cast<float>(std::cos((std::numbers::pi / 180) * m_heading)),
    getPosition().y + halfBody.y * static_cast<float>(std::sin((std::numbers::pi / 180) * m_heading))
  };

  m_heading += (m_speed / (halfBody.x*2.f*0.9f)) * tan((std::numbers::pi / 180) * m_angleWheel)* (180/std::numbers::pi) * time;
  
  taileCar.x -= m_speed * time * std::cos((std::numbers::pi / 180) * m_heading);
  taileCar.y -= m_speed * time * std::sin((std::numbers::pi / 180) * m_heading);
  
  //use new heading
  sf::Vector2f centerPos{
    taileCar.x - halfBody.x * static_cast<float>(std::cos((std::numbers::pi / 180) * m_heading)),
    taileCar.y - halfBody.y * static_cast<float>(std::sin((std::numbers::pi / 180) * m_heading))
  };

  this->setPosition(centerPos);
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