#pragma once
#include <stdexcept>
#include <string>
#include <vector>
#include <istream>
#include <tuple>

/*!
*\file
*\brief File contains structures, operator definitions and headers for functions used in program
*/


/**
* @brief Structure to store coordinates for the point
*/
struct point2d
{
    int x;
    int y;
};

/**
* @brief Operator == for comparison of two points
*/
inline bool operator==(const point2d first, const point2d second)
{
    return first.x == second.x && first.y == second.y;
}

/**
* @brief Operator < for comparison of two points
*/
inline bool operator<(const point2d first, const point2d second)
{
    return std::tie(first.x, first.y) < std::tie(second.x, second.y);
}


/**
* @brief Operator != for comparison of two points
*/
inline bool operator!=(const point2d first, const point2d second)
{
    return !(first == second);
}

/**
* @brief Operator >> for comparison of two points
*/
inline std::istream& operator>>(std::istream& in, point2d& point)
{
    in >> point.x >> point.y;
    return in;
}


/**
* @brief Structure that describes the polygon
*/
struct polygon2d
{
    explicit polygon2d(std::vector<point2d> points);
    explicit polygon2d(std::vector<double> angles);

    /// <summary>Vector of points</summary>
    std::vector<point2d> points;

    /// <summary>Vector of angles</summary>
    std::vector<double> angles;

    void push_back(point2d tmp);

    [[nodiscard]] int points_count() const;

    void push_back(double angle);

    friend bool operator==(const polygon2d& first, const polygon2d& second);
};

/**
* @brief Structure ray
*/
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

/**
* @brief Structure for checking if input data is valid
*/
struct data_check_result
{
    bool is_correct;
    std::string reason;
};

/**
* @brief Structure for errors if
*/
struct data_check_error final : std::invalid_argument
{
    using std::invalid_argument::invalid_argument;
};

/**
* @brief Checks if the point is inside the polygon
* @param[in] - polygon_points - points of the polygon
* @param[in] - point - point
* @return True/False - the point is inside/outside the polygon
*/
bool is_point_inside_polygon(std::vector<point2d> polygon_points, point2d point);

/**
* @brief Checks if input data is correct
* @param[in] - polygon - polygon
* @param[in] - point - point
* @return data_check_result - struct containing boolean variable (isCorrect) and message if data is incorrect
*/
data_check_result check_data(const polygon2d& polygon, point2d point);

/**
* @brief Checks if the point is on the edge of the polygon
* @param[in] - polygon_points - polygon
* @param[in] - point - point
* @return True/False - the point is on the edge/not on the edge the polygon
*/
bool is_point_on_edge_of_polygon(const polygon2d& polygon, struct point2d point);

/**
* @brief Counts the quantity of intersactions between ray and polygon
* @param[in] - polygon - polygon
* @param[in] - ray - ray
* @return int - quantity of intersections
*/
int count_intersects(const polygon2d& polygon, ray2d ray);

/**
* @brief Checks if the ray intersects segment between the points
* @param[in] - first - first point
* @param[in] - last - last point
* @param[in] - ray - ray to intersect the segment
* @return True/False - ray intersects/does not intersect the segment
*/
bool ray_intersects_segment(point2d first, point2d last, ray2d ray);

/**
* @brief Checks if two segment intersect
* @param[in] - first1 - first point of the first segment
* @param[in] - last1 - last point of the first segment
* @param[in] - first2 - first point of the second segment
* @param[in] - last2 - last point of the second segment
* @return True/False - two segments intersect/do not intersect
*/
bool two_segments_intersect(point2d first1, point2d last1, point2d first2, point2d last2);

/**
* @brief Calculates angles quanity of polygon
* @param[in] - polygon - polygon
* @param[in] - point - point
*/
void calculate_angles_for_polygon(polygon2d& polygon, struct point2d point);

/**
* @brief Calculates angle of rotation
* @param[in] - ray - ray
* @param[in] - polygon - polygon
*/
void calculate_angle_of_rotation(ray2d& ray, const polygon2d& polygon);

/**
* @brief Checks if the point is inside the segment
* @param[in] - first - first point of the segment
* @param[in] - last - last point of the segment
* @param[in] - p - the point to check if it is inside the segment
* @return True/False - the point is inside/outside the segment
*/
bool is_point_on_segment(point2d first, point2d last, point2d p);