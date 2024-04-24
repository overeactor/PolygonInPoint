#include "pch.h"

#include <CppUnitTest.h>
#include <CppUnitTestAssert.h>
#include <vector>
#include "../PolygonInPoint/PolygonInPoint.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(IsPointInsidePolygon)
    {
    public:
        TEST_METHOD(PointMatchesVertex)
        {
            const std::vector<point2d> points = {
                {1, 1}, {4, 4}, {6, 1}, {4, 2}
            };
            const point2d point{4, 4};

            Assert::IsTrue(is_point_inside_polygon(points, point));
        }

        TEST_METHOD(PointIsOnSide)
        {
            const std::vector<point2d> points = {
                {1, 1}, {4, 4}, {6, 1}, {4, 2}
            };
            const point2d point{3, 3};

            Assert::IsTrue(is_point_inside_polygon(points, point));
        }

        TEST_METHOD(PointIsAbovePolygon)
        {
            const std::vector<point2d> points = {
                {1, 1}, {4, 4}, {6, 1}, {4, 2}
            };
            const point2d point{1, 5};

            Assert::IsFalse(is_point_inside_polygon(points, point));
        }

        TEST_METHOD(PointIsBelowPolygon)
        {
            const std::vector<point2d> points = {
                {1, 1}, {4, 4}, {6, 1}, {4, 2}
            };
            const point2d point{0, 0};

            Assert::IsFalse(is_point_inside_polygon(points, point));
        }

        TEST_METHOD(PointIsOnTheRightToPolygon)
        {
            const std::vector<point2d> points = {
                {1, 1}, {4, 4}, {6, 1}, {4, 2}
            };
            const point2d point{6, 5};

            Assert::IsFalse(is_point_inside_polygon(points, point));
        }

        TEST_METHOD(PointIsOnTheLeftToPolygon)
        {
            const std::vector<point2d> points = {
                {1, 1}, {4, 4}, {6, 1}, {4, 2}
            };
            const point2d point{1, 2};

            Assert::IsFalse(is_point_inside_polygon(points, point));
        }

        TEST_METHOD(ComplexPolygonAndPointInside)
        {
            const std::vector<point2d> points = {
                {2, 2}, {2, 5}, {4, 4}, {6, 5}, {6, 2}, {4, 1}
            };
            const point2d point{4, 3};

            Assert::IsTrue(is_point_inside_polygon(points, point));
        }
    };
}
