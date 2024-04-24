#include "pch.h"
#include "CppUnitTest.h"
#include "../PolygonInPoint/PolygonInPoint.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(TwoSegmentIntersect)
    {
    public:
        TEST_METHOD(SegmentsAreParallel)
        {
            const point2d first1{1, 1};
            const point2d last1{1, 3};
            const point2d first2{2, 1};
            const point2d last2{2, 3};

            const bool result = two_segments_intersect(first1, last1, first2, last2);

            Assert::AreEqual(false, result);
        }

        TEST_METHOD(SegmentsAreOnSameStraignLineButDoNotIntersect)
        {
            const point2d first1{1, 1};
            const point2d last1{1, 3};
            const point2d first2{1, 4};
            const point2d last2{1, 6};

            const bool result = two_segments_intersect(first1, last1, first2, last2);

            Assert::AreEqual(false, result);
        }

        TEST_METHOD(SegmentsAreOnSameStraignLineAndDoIntersect)
        {
            const point2d first1{2, 1};
            const point2d last1{2, 3};
            const point2d first2{2, 2};
            const point2d last2{2, 4};

            const bool result = two_segments_intersect(first1, last1, first2, last2);

            Assert::AreEqual(true, result);
        }

        TEST_METHOD(SegmentsArePerpendicular)
        {
            const point2d first1{1, 2};
            const point2d last1{3, 2};
            const point2d first2{2, 1};
            const point2d last2{2, 3};


            const bool result = two_segments_intersect(first1, last1, first2, last2);

            Assert::AreEqual(true, result);
        }

        TEST_METHOD(SegmentsAreCrissCross)
        {
            const point2d first1{1, 3};
            const point2d last1{3, 2};
            const point2d first2{1, 2};
            const point2d last2{3, 3};

            const bool result = two_segments_intersect(first1, last1, first2, last2);

            Assert::AreEqual(true, result);
        }

        TEST_METHOD(SegmentsAreSame)
        {
            const point2d first1{1, 3};
            const point2d last1{3, 2};
            const point2d first2{1, 3};
            const point2d last2{3, 2};

            const bool result = two_segments_intersect(first1, last1, first2, last2);

            Assert::AreEqual(true, result);
        }

        TEST_METHOD(SegmentsHaveSameVertex)
        {
            const point2d first1{2, 1};
            const point2d last1{2, 3};
            const point2d first2{2, 1};
            const point2d last2{3, 1};

            const bool result = two_segments_intersect(first1, last1, first2, last2);

            Assert::AreEqual(true, result);
        }
    };
}
