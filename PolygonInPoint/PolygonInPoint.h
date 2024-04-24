#pragma once
#include <stdexcept>
#include <string>
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

inline bool operator<(const point2d first, const point2d second)
{
    return std::tie(first.x, first.y) < std::tie(second.x, second.y);
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

struct data_check_result
{
    bool is_correct;
    std::string reason;
};

struct data_check_error final : std::invalid_argument
{
    using std::invalid_argument::invalid_argument;
};

bool is_point_inside_polygon(std::vector<point2d> polygon_points, point2d point);
data_check_result check_data(const polygon2d& polygon, point2d point);
bool is_point_on_edge_of_polygon(const polygon2d& polygon, struct point2d point);
int count_intersects(const polygon2d& polygon, ray2d ray);