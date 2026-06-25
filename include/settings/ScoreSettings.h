#pragma once

// Tunable scoring / rating values. The stopwatch counts UP while playing;
// when the player parks, the elapsed time is turned into a star rating and
// a numeric score (faster + fewer bumps = higher score).
namespace scoreCfg
{
  // Base points awarded for completing a level before any penalties.
  constexpr int   BASE_POINTS = 1000;

  // Points subtracted per second elapsed.
  constexpr int   PENALTY_PER_SECOND = 20;

  // Points subtracted per collision survived during the attempt.
  constexpr int   PENALTY_PER_BUMP = 75;

  // Score never drops below this.
  constexpr int   MIN_POINTS = 50;

  // Star rating thresholds, in seconds (<= time => that many stars).
  constexpr float THREE_STARS_UNDER = 12.f;
  constexpr float TWO_STARS_UNDER   = 25.f;
  // anything slower than TWO_STARS_UNDER => one star
}
