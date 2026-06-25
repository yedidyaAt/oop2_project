#include "Progress.h"

#include "json.hpp"

#include <fstream>

Progress& Progress::getInstance()
{
  static Progress instance;
  return instance;
}

void Progress::init(std::size_t totalLevels)
{
  m_total = totalLevels;
  m_best.assign(m_total, -1.f);
  m_unlockedCount = 1;
  load();
}

void Progress::load()
{
  using json = nlohmann::json;

  std::ifstream file(m_path);
  if (!file.is_open())
    return; // no save yet -> defaults

  try {
    json j = json::parse(file);

    m_unlockedCount = j.value("unlockedCount", std::size_t{ 1 });

    if (m_unlockedCount < 1)
      m_unlockedCount = 1;

    if (m_unlockedCount > m_total)
      m_unlockedCount = m_total;

    if (j.contains("best") && j.at("best").is_array())
    {
      const auto& arr = j.at("best");
      for (std::size_t i = 0; i < m_total && i < arr.size(); ++i)
        m_best[i] = arr[i].get<float>();
    }
  }
  catch (const json::exception&)
  {
    // corrupt save -> ignore and keep defaults
  }
}

void Progress::save() const
{
  using json = nlohmann::json;

  json j;
  j["unlockedCount"] = m_unlockedCount;
  j["best"] = m_best;

  std::ofstream file(m_path);
  if (file.is_open())
    file << j.dump(2);
}

bool Progress::isUnlocked(std::size_t levelIndex) const
{
  return levelIndex < m_unlockedCount;
}

std::optional<float> Progress::bestTime(std::size_t levelIndex) const
{
  if (levelIndex >= m_total) return std::nullopt;
  if (m_best[levelIndex] < 0.f) return std::nullopt;
  return m_best[levelIndex];
}

bool Progress::recordCompletion(std::size_t levelIndex, float seconds)
{
  if (levelIndex >= m_total)
    return false;

  // unlock next level
  if (levelIndex + 1 >= m_unlockedCount && levelIndex + 1 <= m_total)
    m_unlockedCount = levelIndex + 2 <= m_total ? levelIndex + 2 : m_total;

  bool newBest = false;
  if (m_best[levelIndex] < 0.f || seconds < m_best[levelIndex])
  {
    m_best[levelIndex] = seconds;
    newBest = true;
  }

  save();
  return newBest;
}

std::size_t Progress::unlockedCount() const { return m_unlockedCount; }
std::size_t Progress::totalLevels() const { return m_total; }

void Progress::resetAll()
{
  m_unlockedCount = 1;
  m_best.assign(m_total, -1.f);
  save();
}
