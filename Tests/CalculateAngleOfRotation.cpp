#include "pch.h"

#include <CppUnitTest.h>
#include <CppUnitTestAssert.h>
#include <vector>
#include "../PolygonInPoint/PolygonInPoint.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(CalculateAngleOfRotation)
    {
    public:
        TEST_METHOD(OneOfPolygonAnglesIsZero)
        {
            const std::vector<double> angles = {
                {0, 90, 90, 180}
            };
            const polygon2d polygon(angles);
            ray2d ray{0, 0};

            calculate_angle_of_rotation(ray, polygon);

            ray2d expectedRay{0, 0};
            expectedRay.angle = 45;

            Assert::IsTrue(expectedRay == ray);
        }

        TEST_METHOD(TwoOfPolygonAnglesAreZero)
        {
            const std::vector<double> angles = {
                {0, 0, 20, 60}
            };
            const polygon2d polygon(angles);
            ray2d ray{0, 0};

            calculate_angle_of_rotation(ray, polygon);

            ray2d expectedRay{0, 0};
            expectedRay.angle = 10;

            Assert::IsTrue(expectedRay == ray);
        }

        TEST_METHOD(SomeOfPolygonAnglesAreZero)
        {
            const std::vector<double> angles = {
                {0, 0, 0, 0, 15, -20, 30, -30, -45}
            };
            const polygon2d polygon(angles);
            ray2d ray{0, 0};

            calculate_angle_of_rotation(ray, polygon);

            ray2d expectedRay{0, 0};
            expectedRay.angle = 7.5;

            Assert::IsTrue(expectedRay == ray);
        }

        TEST_METHOD(PolygonAnglesLocatedIn1stQuarter)
        {
            const std::vector<double> angles = {
                {15, 20, -60, 70}
            };
            const polygon2d polygon(angles);
            ray2d ray{0, 0};

            calculate_angle_of_rotation(ray, polygon);

            ray2d expectedRay{0, 0};
            expectedRay.angle = 0;

            Assert::IsTrue(expectedRay == ray);
        }

        TEST_METHOD(PolygonAnglesLocatedIn2ndQuarter)
        {
            const std::vector<double> angles = {
                {110, -130, 150, 150, 160, 180}
            };
            const polygon2d polygon(angles);
            ray2d ray{0, 0};

            calculate_angle_of_rotation(ray, polygon);

            ray2d expectedRay{0, 0};
            expectedRay.angle = 0;

            Assert::IsTrue(expectedRay == ray);
        }

        TEST_METHOD(PolygonAnglesLocatedIn3rdQuarter)
        {
            const std::vector<double> angles = {
                {-100, 150, -150, -170, 180}
            };
            const polygon2d polygon(angles);
            ray2d ray{0, 0};

            calculate_angle_of_rotation(ray, polygon);

            ray2d expectedRay{0, 0};
            expectedRay.angle = 0;

            Assert::IsTrue(expectedRay == ray);
        }

        TEST_METHOD(PolygonAnglesLocatedIn4thQuarter)
        {
            const std::vector<double> angles = {
                {-20, 90, -90, -135}
            };
            const polygon2d polygon(angles);
            ray2d ray{0, 0};

            calculate_angle_of_rotation(ray, polygon);

            ray2d expectedRay{0, 0};
            expectedRay.angle = 0;

            Assert::IsTrue(expectedRay == ray);
        }
    };
}
