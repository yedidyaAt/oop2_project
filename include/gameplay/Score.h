#pragma once

// Turns "how long did it take" + "how many bumps" into a numeric score and a
// 1..3 star rating. All thresholds live in ScoreSettings.h so they are tunable.
class Score
{
public:
  Score() = default;

  // Compute final score for a finished level.
  void compute(float elapsedSeconds, int bumps);

  int   points() const;
  int   stars() const;   // 1, 2 or 3

private:
  int m_points = 0;
  int m_stars  = 0;
};
