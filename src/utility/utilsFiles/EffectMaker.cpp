#include "EffectMaker.h"
#include "SmokeAnimation.h"
#include "Effects.h"
#include "ResourceManager.h"

namespace effectMaker
{
  std::unique_ptr<Animation> makeSmokeLoop(sf::Vector2f pos)
  {
    return std::make_unique<SmokeAnimation>(
      ResourceManager::getInstance().getTextureEffects(Effects::SMOKE),
      pos,true);
  }
}