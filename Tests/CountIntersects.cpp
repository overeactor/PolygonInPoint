#include "pch.h"
#include "CppUnitTest.h"
#include "../PolygonInPoint/PolygonInPoint.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(CountIntersecets)
    {
    public:
        TEST_METHOD(NoIntersections)
        {
            const std::vector<point2d> points = {
                {1, 1}, {4, 5}, {6, 1}, {4, 3}
            };
            const polygon2d polygon(points);
            const ray2d ray{0, 0};

            const auto result = count_intersects(polygon, ray);

            Assert::AreEqual(0, result);
        }

        TEST_METHOD(OneIntersection)
        {
            const std::vector<point2d> points = {
                {1, 1}, {4, 5}, {6, 1}, {4, 3}
            };
            const polygon2d polygon(points);
            const ray2d ray{4, 4};

            const auto result = count_intersects(polygon, ray);

            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TwoIntersections)
        {
            const std::vector<point2d> points = {
                {1, 1}, {4, 5}, {6, 1}, {4, 3}
            };
            const polygon2d polygon(points);
            const ray2d ray{1, 4};

            const auto result = count_intersects(polygon, ray);

            Assert::AreEqual(2, result);
        }

        TEST_METHOD(EvenNumberOfIntersections)
        {
            const std::vector<point2d> points = {
                {1, 1}, {4, 5}, {6, 1}, {4, 3}
            };
            const polygon2d polygon(points);
            const ray2d ray{0, 2};

            const auto result = count_intersects(polygon, ray);

            Assert::AreEqual(4, result);
        }

        TEST_METHOD(OddNumberOfIntersections)
        {
            const std::vector<point2d> points = {
                {1, 1}, {4, 5}, {6, 1}, {4, 3}
            };
            const polygon2d polygon(points);
            const ray2d ray{3, 3};

            const auto result = count_intersects(polygon, ray);

            Assert::AreEqual(3, result);
        }
    };
}
