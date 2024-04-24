#include <clocale>
#include <fstream>
#include <iostream>
#include <vector>

#include "PolygonInPoint.h"

/*!
*\file
*\brief File main function that calls functions from PolygonInPoint.cpp
*\mainpage Documentation for program "PolygonInPoint"

There is given a set of variable types used in the main code without defining classes, as well as a set of method calls and their arguments called in the main code. 
Generate interface code for the variable classes declared in this functions based on operations on given variables. 
That means that the method call must be mapped into the method definition, where the formal parameters must be the passed values.
Take into account ambiguities when defining methods and fields based on access to them, as well as the possibility of overloading methods.
Consider the operators and their types that can be inferred.

Sample program start
*\code
PolygonInPoint.exe 1.txt
*\endcode
*\author Bebahani A.A.
*\date April 2024
*\version 1.0
*/

int main()
{
    setlocale(LC_ALL, "UTF-8");

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