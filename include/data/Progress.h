#pragma once

#include <string>
#include <vector>
#include <optional>

// Persistent player progress, stored in progress.json next to the executable.
//  - m_unlockedCount: how many levels are unlocked (index 0..n-1). Level 0 is
//    always unlocked; finishing level i unlocks level i+1.
//  - best time per level index.
class Progress
{
public:
  static Progress& getInstance();

  Progress(const Progress&) = delete;
  Progress& operator=(const Progress&) = delete;

  // Must be called once at startup with the total number of levels.
  void init(std::size_t totalLevels);

  bool isUnlocked(std::size_t levelIndex) const;
  std::optional<float> bestTime(std::size_t levelIndex) const;

  // Records a completion. Unlocks the next level and updates best time.
  // Returns true if this is a new best time for that level.
  bool recordCompletion(std::size_t levelIndex, float seconds);

  std::size_t unlockedCount() const;
  std::size_t totalLevels() const;

  // Wipes all progress back to "only level 1 unlocked" and saves.
  void resetAll();

private:
  Progress() = default;

  void load();
  void save() const;

  std::string m_path = "progress.json";
  std::size_t m_total = 0;
  std::size_t m_unlockedCount = 1;
  std::vector<float> m_best;   // size == m_total, negative means "no time yet"
};
