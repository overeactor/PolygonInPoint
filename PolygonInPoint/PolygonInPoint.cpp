#include "PolygonInPoint.h"

#include <algorithm>
#include <functional>
#include <set>

constexpr auto rad = 0.0174533;

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
const std::string point_max_value_string = std::to_string(point_max_value);
const std::string point_min_value_string = std::to_string(point_min_value);
constexpr int min_point_count = 3;
constexpr int max_point_count = 50;

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

bool any_polygon_sides_intersect(const polygon2d& polygon)
{
    const int count = polygon.points_count();
    for (int i = 0; i <= count - 2; i++)
    {
        for (int j = 0; j <= count - 2; j++)
        {
            if (two_segments_intersect(polygon.points[i], polygon.points[i + 1],
                polygon.points[j], polygon.points[j + 1])
                && i != j && abs(i - j) != 1)
            {
                return true;
            }
        }
    }

    for (int i = 1; i <= count - 3; i++)
    {
        if (two_segments_intersect(polygon.points[0], polygon.points[count - 1],
            polygon.points[i], polygon.points[i + 1]))
        {
            return true;
        }
    }

    return false;
}

data_check_result check_data(const polygon2d& polygon, const point2d point)
{
    if (const int count = polygon.points_count(); count < min_point_count || count > max_point_count)
    {
        return {
            false,
            "The number of points must be in the range [" + std::to_string(min_point_count) + "; " + std::to_string(
                max_point_count) + "]"
        };
    }

    if (!is_point_valid(point))
    {
        return {
            false,
            "The coordinates of the point must not exceed the allowed range [" + point_min_value_string + "; " +
            point_max_value_string + "]"
        };
    }

    if (const auto not_valid_point_iter =
        std::find_if(polygon.points.begin(),
            polygon.points.end(),
            std::not_fn(is_point_valid));
        not_valid_point_iter != polygon.points.end())
    {
        return {
            false,
            "The coordinates of the polygon's point " + std::to_string(
                not_valid_point_iter - polygon.points.begin() + 1) +
            " must not exceed the allowed range [" + point_min_value_string + "; " + point_max_value_string + "]"
        };
    }

    if (any_points_match(polygon))
    {
        return { false, "The points of the polygon must not match" };
    }

    if (any_polygon_sides_intersect(polygon))
    {
        return { false, "The polygon sides must not intersect" };
    }

    return { true, "" };
}

bool is_point_on_segment(const point2d first, const point2d last, const point2d p)
{
    const bool is_segment_vertical = first.x == last.x;
    const bool is_segment_horizontal = first.y == last.y;
    if (is_segment_vertical)
    {
        if (first.x == p.x &&
            (first.y >= p.y && p.y >= last.y ||
                last.y >= p.y && p.y >= first.y))
            return true;
    }
    else if (is_segment_horizontal)
    {
        if (first.y == p.y &&
            (first.x >= p.x && p.x >= last.x ||
                last.x >= p.x && p.x >= first.x))
            return true;
    }
    else
    {
        if ((p.x - first.x) * (last.y - first.y) - (p.y - first.y) * (last.x - first.x) == 0 && (first.x <= p.x && p.x
            <= last.x || last.x <= p.x && p.x <= first.x))
            return true;
    }


    return false;
}

bool is_point_on_edge_of_polygon(const polygon2d& polygon, const point2d point)
{
    if (is_point_on_segment(polygon.points[0],
        polygon.points[polygon.points_count() - 1], point))
        return true;

    for (int i = 0; i < polygon.points_count() - 1; i++)
    {
        if (is_point_on_segment(polygon.points[i], polygon.points[i + 1], point))
            return true;
    }

    return false;
}

void calculate_angles_for_polygon(polygon2d& polygon, const point2d point)
{
    for (const auto [x, y] : polygon.points)
    {
        const point2d h = { x, point.y };

        const double z = (point.x - h.x) * (point.x - h.x) + (h.y - y) * (h.y - y);

        const double cos = abs(point.x - h.x) / sqrt(z);
        double angle = acos(cos) / rad;

        if (x < point.x)
            angle = 180 - angle;

        if (y < point.y)
            angle *= -1;

        polygon.push_back(angle);
    }
}

bool two_segments_intersect(const point2d first1, const point2d last1, const point2d first2, const point2d last2)
{
    const int a1 = first1.y - last1.y;
    const int b1 = last1.x - first1.x;
    const int c1 = first1.x * last1.y - last1.x * first1.y;

    const int coef1 = a1 * first2.x + b1 * first2.y + c1;
    const int coef2 = a1 * last2.x + b1 * last2.y + c1;

    const int a2 = first2.y - last2.y;
    const int b2 = last2.x - first2.x;
    const int c2 = first2.x * last2.y - last2.x * first2.y;

    const int coef3 = a2 * first1.x + b2 * first1.y + c2;
    const int coef4 = a2 * last1.x + b2 * last1.y + c2;

    if (coef1 >= 0 && coef2 < 0 && coef3 >= 0 && coef4 < 0 || //11
        coef1 <= 0 && coef2 > 0 && coef3 >= 0 && coef4 < 0 ||
        coef1 >= 0 && coef2 < 0 && coef3 <= 0 && coef4 > 0 ||
        coef1 <= 0 && coef2 > 0 && coef3 <= 0 && coef4 > 0 ||

        coef1 >= 0 && coef2 < 0 && coef3 > 0 && coef4 <= 0 || //12
        coef1 <= 0 && coef2 > 0 && coef3 > 0 && coef4 <= 0 ||
        coef1 >= 0 && coef2 < 0 && coef3 < 0 && coef4 >= 0 ||
        coef1 <= 0 && coef2 > 0 && coef3 < 0 && coef4 >= 0 ||

        coef1 > 0 && coef2 <= 0 && coef3 >= 0 && coef4 < 0 || //21
        coef1 < 0 && coef2 >= 0 && coef3 >= 0 && coef4 < 0 ||
        coef1 > 0 && coef2 <= 0 && coef3 <= 0 && coef4 > 0 ||
        coef1 < 0 && coef2 >= 0 && coef3 <= 0 && coef4 > 0 ||

        coef1 > 0 && coef2 <= 0 && coef3 > 0 && coef4 <= 0 || //22
        coef1 < 0 && coef2 >= 0 && coef3 > 0 && coef4 <= 0 ||
        coef1 > 0 && coef2 <= 0 && coef3 < 0 && coef4 >= 0 ||
        coef1 < 0 && coef2 >= 0 && coef3 < 0 && coef4 >= 0)

        return true;


    if (coef1 == 0 && coef2 == 0 && coef3 == 0 && coef4 == 0)
        return (first1.x >= first2.x && first2.x >= last1.x || first1.x >= last2.x && last2.x >= last1.x ||
            first2.x >= first1.x && first1.x >= last2.x || first2.x >= last1.x && last1.x >= last2.x ||
            last1.x >= first2.x && first2.x >= first1.x || last1.x >= last2.x && last2.x >= first1.x ||
            last2.x >= first1.x && first1.x >= first2.x || last2.x >= last1.x && last1.x >= first2.x) &&
        (first1.y >= first2.y && first2.y >= last1.y || first1.y >= last2.y && last2.y >= last1.y ||
            first2.y >= first1.y && first1.y >= last2.y || first2.y >= last1.y && last1.y >= last2.y ||
            last1.y >= first2.y && first2.y >= first1.y || last1.y >= last2.y && last2.y >= first1.y ||
            last2.y >= first1.y && first1.y >= first2.y || last2.y >= last1.y && last1.y >= first2.y);
    return false;
}

bool ray_intersects_segment(const point2d first, const point2d last, const ray2d ray)
{
    const double angle = atan(ray.tg) / rad;
    const double sn = floor(sin(angle * rad) * 1000) / 1000;
    const double cs = floor(cos(angle * rad) * 1000) / 1000;

    const double nom_s = sn * (ray.x - last.x) + cs * (last.y - ray.y);
    const double denom_s = sn * (first.x - last.x) + cs * (last.y - first.y);
    double s = nom_s / denom_s;

    if (nom_s == 0)
        s = 0;

    const double nom_t = s * first.x + (1 - s) * last.x - ray.x;
    double t = nom_t / cs;

    if (nom_t == 0)
        t = 0;

    return t >= 0 && s >= 0 && s <= 1;
}

int count_intersects(const polygon2d& polygon, const ray2d ray)
{
    int count = 0;

    if (ray_intersects_segment(polygon.points.front(), polygon.points.back(), ray))
        count++;

    for (int i = 0; i < polygon.points_count() - 1; i++)
        if (ray_intersects_segment(polygon.points[i], polygon.points[i + 1], ray))
            count++;

    return count;
}

void calculate_angle_of_rotation(ray2d& ray, const polygon2d& polygon)
{
    if (polygon.angles[0] != 0)
        ray.angle = 0;
    else
    {
        for (const auto angle : polygon.angles)
            if (angle != 0)
            {
                ray.angle = angle / 2;
                break;
            }
    }

    ray.sin = sin(ray.angle * rad);
    ray.cos = cos(ray.angle * rad);

    if (ray.cos != 0)
        ray.tg = ray.sin / ray.cos;
}