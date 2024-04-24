#include "PolygonInPoint.h"

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