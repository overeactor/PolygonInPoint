#include "PolygonInPoint.h"

#include <set>

bool operator==(const polygon2d& first, const polygon2d& second)
{
    if (first.points_count() != second.points_count())
        return false;

    for (int i = 0; i < first.points_count(); i++)
        if (abs(first.points[i].x - second.points[i].x) > 0.01 ||
            abs(first.points[i].y - second.points[i].y) > 0.01)
            return false;

    for (int i = 0; i < first.points_count(); i++)
        if (abs(first.angles[i] - second.angles[i]) > 0.01)
            return false;

    return true;
}

constexpr int point_max_value = 1000;
constexpr int point_min_value = -1000;

bool is_point_valid(const point2d point)
{
    return point.x >= point_min_value && point.x <= point_max_value && point.y >= point_min_value && point.y <=
        point_max_value;
}

bool any_points_match(const polygon2d& polygon)
{
    std::set<point2d> visited;

    for (const auto point : polygon.points)
    {
        if (visited.count(point) > 0)
            return true;
        visited.insert(point);
    }

    return false;
}