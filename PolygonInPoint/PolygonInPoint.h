#pragma once
struct point2d
{
    int x;
    int y;
};

inline bool operator==(const point2d first, const point2d second)
{
    return first.x == second.x && first.y == second.y;
}