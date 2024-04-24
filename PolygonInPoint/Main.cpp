#include <clocale>
#include <fstream>
#include <iostream>
#include <vector>

#include "PolygonInPoint.h"

int main()
{
    setlocale(LC_CTYPE, "rus");

    std::string path_to_file;

    std::cout << "Enter path to file: ";
    std::cin >> path_to_file;

    std::ifstream fs(path_to_file);

    if (!fs.is_open())
    {
        std::cout << "Cannot open the file" << std::endl;
        std::cin.get();
        return 0;
    }

    int points_count{};
    fs >> points_count;
    std::vector<point2d> points(points_count);
    for (auto& point : points)
    {
        fs >> point;
    }

    point2d point_to_check{};
    fs >> point_to_check;

    try
    {
        if (is_point_inside_polygon(points, point_to_check))
            std::cout << "1" << std::endl;
        else
            std::cout << "0" << std::endl;
    }
    catch (std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
    }
}