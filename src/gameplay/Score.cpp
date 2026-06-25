#include "Score.h"
#include "ScoreSettings.h"

#include <algorithm>

void Score::compute(float elapsedSeconds, int bumps)
{
  int raw = scoreCfg::BASE_POINTS
          - static_cast<int>(elapsedSeconds) * scoreCfg::PENALTY_PER_SECOND
          - bumps * scoreCfg::PENALTY_PER_BUMP;

  m_points = std::max(scoreCfg::MIN_POINTS, raw);

  if (elapsedSeconds <= scoreCfg::THREE_STARS_UNDER)
    m_stars = 3;
  else if (elapsedSeconds <= scoreCfg::TWO_STARS_UNDER)
    m_stars = 2;
  else
    m_stars = 1;
}

int Score::points() const
{
  return m_points;
}

int Score::stars() const
{
  return m_stars;
}
