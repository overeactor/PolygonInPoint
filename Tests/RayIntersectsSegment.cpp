#include "pch.h"
#include "CppUnitTest.h"
#include "../PolygonInPoint/PolygonInPoint.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(RayIntersectsSegment)
    {
    public:
        TEST_METHOD(RayAndSegmentAreParallel)
        {
            const point2d first{2, 2};
            const point2d last{4, 2};
            const ray2d ray{1, 1};

            const bool result = ray_intersects_segment(first, last, ray);

            Assert::AreEqual(false, result);
        }

        TEST_METHOD(RayAndSegmentOnSameStraignLineButDoNotIntersect)
        {
            const point2d first{1, 1};
            const point2d last{3, 1};
            const ray2d ray{4, 1};

            const bool result = ray_intersects_segment(first, last, ray);

            Assert::AreEqual(false, result);
        }

        TEST_METHOD(RayAndSegmentOnSameStraignLineAndDoIntersect)
        {
            const point2d first{3, 3};
            const point2d last{4, 4};
            ray2d ray{2, 2};
            ray.tg = 1;

            const bool result = ray_intersects_segment(first, last, ray);

            Assert::AreEqual(true, result);
        }

        TEST_METHOD(RayAndSegmentAreCrissCross)
        {
            const point2d first{1, 2};
            const point2d last{3, 1};
            ray2d ray{2, 1};
            ray.tg = 1;

            const bool result = ray_intersects_segment(first, last, ray);

            Assert::AreEqual(true, result);
        }

        TEST_METHOD(RayAndSegmentArePerpendicular)
        {
            const point2d first{2, 2};
            const point2d last{3, 1};
            ray2d ray{2, 1};
            ray.tg = 1;

            const bool result = ray_intersects_segment(first, last, ray);

            Assert::AreEqual(true, result);
        }

        TEST_METHOD(RayIntersects)
        {
            const point2d first{2, 2};
            const point2d last{5, 1};
            ray2d ray{2, 2};
            ray.tg = 1;

            const bool result = ray_intersects_segment(first, last, ray);

            Assert::AreEqual(true, result);
        }

        TEST_METHOD(RayIntersects2)
        {
            const point2d first{2, 2};
            const point2d last{4, 4};
            const ray2d ray{3, 3};

            const bool result = ray_intersects_segment(first, last, ray);

            Assert::AreEqual(true, result);
        }

        TEST_METHOD(RayStartsAtSegmentPoint)
        {
            const point2d first{2, 2};
            const point2d last{5, 2};
            ray2d ray{2, 2};
            ray.tg = 1;

            const bool result = ray_intersects_segment(first, last, ray);

            Assert::AreEqual(true, result);
        }
    };
}
