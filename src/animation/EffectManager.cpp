#include "EffectManager.h"

#include <utility>

void EffectManager::add(std::unique_ptr<Animation> effect)
{
  m_effects.push_back(std::move(effect));
}

void EffectManager::update(sf::Time time)
{
  for (auto& effect : m_effects)
  {
    effect->update(time);
  }

  deleteFinishedEffect();
}

void EffectManager::draw(sf::RenderWindow& window)const
{
  for (auto& effect : m_effects)
  {
    effect->draw(window);
  }
}

void EffectManager::deleteFinishedEffect()
{
  m_effects.erase(std::remove_if(m_effects.begin(), 
                                 m_effects.end(),
                                [](const std::unique_ptr<Animation>& a)
                                {
                                  return a->isFinished();
                                }),
                  m_effects.end());
}
