#pragma once
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