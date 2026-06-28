#include "Collision.h"


namespace collision
{

  static std::array<sf::Vector2f, 2> getAxes(const std::array<sf::Vector2f, 4>& rec)
  {
    sf::Vector2f axis = rec[1] - rec[0];
    sf::Vector2f perpendicularToAxes1 = { axis.y,-axis.x };

    return std::array<sf::Vector2f, 2> {axis, perpendicularToAxes1};
  }

  static std::array<sf::Vector2f, 4> getAxes(const std::array<sf::Vector2f, 4>& recA, const std::array<sf::Vector2f, 4>& recB)
  {
    const auto arr1 = getAxes(recA);
    const auto arr2 = getAxes(recB);

    return std::array<sf::Vector2f, 4>{arr1[0], arr1[1], arr2[0], arr2[1]};
  }
  static sf::Vector2f getProjection(const sf::Vector2f& axis, const std::array<sf::Vector2f, 4>& rec)
  {
    float min = 0, max = 0;

    min = axis.dot(rec[0]);
    max = axis.dot(rec[1]);

    if (min > max)
    {
      float temp = min;
      min = max;
      max = temp;
    }

    float scalar = 0;
    for (int i = 2;i < 4; i++)
    {
      scalar = axis.dot(rec[i]);

      if (scalar > max)
      {
        max = scalar;
      }
      else if (scalar < min)
      {
        min = scalar;
      }
    }

    return sf::Vector2f{ min,max };
  }

  static bool overlap(const sf::Vector2f& v1, const sf::Vector2f& v2)
  {
    return v1.y >= v2.x && v2.y >= v1.x; //maxA >= minB && maxB >= minA
  }

}

std::array<sf::Vector2f,4> collision::getGlobalPoints(const sf::FloatRect& rec,
                                                       const sf::Transform& trans)
{
  // Shrink the rect toward its own center by HITBOX_SCALE, so transparent
  // padding around the sprite is not counted as part of the body.
  const sf::Vector2f center = rec.position + rec.size / 2.f;
  const sf::Vector2f half = (rec.size / 2.f) * collision::HITBOX_SCALE;

  std::array<sf::Vector2f, 4> points
  {
    sf::Vector2f{ center.x - half.x, center.y - half.y }, // top-left
    sf::Vector2f{ center.x + half.x, center.y - half.y }, // top-right
    sf::Vector2f{ center.x + half.x, center.y + half.y }, // bottom-right
    sf::Vector2f{ center.x - half.x, center.y + half.y }, // bottom-left
  };

  for (int i = 0; i < 4; i++)
    points[i] = trans.transformPoint(points[i]);

  return points;
}

sf::Vector2f collision::hitPointByClosestCorners(const std::array<sf::Vector2f, 4>& carCorners, const std::array<sf::Vector2f, 4>& objCorners)
{
  float minDistSq = std::numeric_limits<float>::max();  // smallest distance found so far
  sf::Vector2f bestCarCorner, bestObjCorner;

  // iterate over every pair of corners (car corner x obstacle corner)
  for (const auto& carC : carCorners)
  {
    for (const auto& objC : objCorners)
    {
      // squared distance between the two corners
      float dx = carC.x - objC.x;
      float dy = carC.y - objC.y;
      float distSq = dx * dx + dy * dy;

      // if this is the closest pair so far, keep it
      if (distSq < minDistSq)
      {
        minDistSq = distSq;
        bestCarCorner = carC;
        bestObjCorner = objC;
      }
    }
  }

  // midpoint between the two closest corners
  return (bestCarCorner + bestObjCorner) / 2.f;
}

bool collision::overlaps(const std::array<sf::Vector2f, 4>& recA, const std::array<sf::Vector2f, 4>& recB)
{
  const std::array<sf::Vector2f, 4> axes = getAxes(recA, recB);

  for (const auto& axis : axes)
  {
    const auto projection1 = getProjection(axis, recA);
    const auto projection2 = getProjection(axis, recB);

    if (!overlap(projection1, projection2))
      return false;
  }

  return true;
}
