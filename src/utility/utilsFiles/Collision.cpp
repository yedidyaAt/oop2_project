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
  std::array<sf::Vector2f,4> points
  {
    rec.position, // top left
    {rec.position + sf::Vector2f{rec.size.x,0.f}},//topRight
    {rec.position + sf::Vector2f{rec.size.x,rec.size.y}}, //bottomRight
    {rec.position + sf::Vector2f{0.f,rec.size.y}},//bottomLeft
  };

  for (int i = 0; i < 4;i++)
  {
    points[i] = trans.transformPoint(points[i]);
  }


  return points;
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
