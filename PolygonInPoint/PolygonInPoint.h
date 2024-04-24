#pragma once
#include <vector>
#include <istream>
struct point2d
{
    int x;
    int y;
};

inline bool operator==(const point2d first, const point2d second)
{
    return first.x == second.x && first.y == second.y;
}

inline bool operator!=(const point2d first, const point2d second)
{
    return !(first == second);
}

inline std::istream& operator>>(std::istream& in, point2d& point)
{
    in >> point.x >> point.y;
    return in;
}

struct polygon2d
{
    explicit polygon2d(std::vector<point2d> points);
    explicit polygon2d(std::vector<double> angles);

    std::vector<point2d> points;
    std::vector<double> angles;

    void push_back(point2d tmp);

    [[nodiscard]] int points_count() const;

    void push_back(double angle);

    friend bool operator==(const polygon2d& first, const polygon2d& second);
};

struct ray2d
{
    ray2d(const int x, const int y) : x{ x }, y{ y }
    {
    }


    int x{};
    int y{};
    double angle{};
    double sin{ 2 };
    double cos{ 2 };
    double tg{};

    friend bool operator==(ray2d first, ray2d second);
};

bool is_point_inside_polygon(std::vector<point2d> polygon_points, point2d point);