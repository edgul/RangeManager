#include "RangeManagerTest.h"

#include <iostream>

RangeManagerTest::RangeManagerTest() : invalidRangeTestNum_(0)
  , validRangeTestNum_(0)
  , startEndRangeTestNum_(0)
  , clearRangeTestNum_(0)
{

}

void RangeManagerTest::invalidRanges()
{
    std::cout << "######### Invalid Range Test" << std::endl;
    invalidRange(0, 0);
    invalidRange(0, -1);
    invalidRange(2, 0);
    invalidRange(10000,0);
    invalidRange(0,-10000);
    invalidRange(0, 0);
}

void RangeManagerTest::validRanges()
{
    std::cout << "######### Valid Range Test" << std::endl;
    validRange(0, 1);
    validRange(1, 10);
    validRange(1, 100);
    validRange(1, 1000);
    validRange(10, 10000);
    validRange(100, 100000);
    validRange(1000, 100000);
    validRange(-1, 0);
    validRange(-1, 10);
    validRange(-100, 100);
    validRange(-1000, 1000);
    validRange(-10000, 10000);
}

void RangeManagerTest::clearRanges()
{
    std::cout << "######### Clear Range Test" << std::endl;

    Range r0 = Range(0,1);
    passIfCondTrue(r0.valid());
    std::cout << std::endl;
    r0.clear();
    passIfCondTrue(r0.valid() == false);
    std::cout << std::endl;

    Range r1 = Range(-1, 1);
    passIfCondTrue(r1.valid());
    std::cout << std::endl;
    r1.clear();
    passIfCondTrue(r1.valid() == false);
    std::cout << std::endl;
}

void RangeManagerTest::toVecRanges()
{

}

void RangeManagerTest::startEndRanges()
{
    std::cout << "######### Start/End Range Test" << std::endl;

    auto r0 = Range(0, 1);
    auto r1 = Range(0, 1);
    sameStartRange(r0, r0, true);
    sameEndRange(r0, r0, true);
    sameStartRange(r0, r1, true);
    sameEndRange(r0, r1, true);

    auto r2 = Range(0, 2);
    sameStartRange(r1, r2, true);
    sameEndRange(r1, r2, false);

    auto r3 = Range(-1, 2);
    sameStartRange(r1, r3, false);
    sameEndRange(r1, r3, false);

    auto r4 = Range(-40,100);
    auto r5 = Range(-500,1000);
    sameStartRange(r4, r5, false);
    sameEndRange(r4, r5, false);
}

void RangeManagerTest::passIfCondTrue(bool cond)
{
    if (cond)
    {
        std::cout << "PASS";
    }
    else
    {
        std::cout << "FAIL";
    }
}

void RangeManagerTest::invalidRange(int start, int end)
{
    Range r = Range(start, end);
    std::cout << invalidRangeTestNum_ << ". ";
    passIfCondTrue(r.valid() == false);
    std::cout << std::endl;
    invalidRangeTestNum_++;
}

void RangeManagerTest::validRange(int start, int end)
{
    Range r = Range(start, end);
    std::cout << validRangeTestNum_ << ". ";
    passIfCondTrue(r.valid());
    std::cout << std::endl;
    validRangeTestNum_++;
}

void RangeManagerTest::sameStartRange(Range &range1, Range &range2, bool expected)
{
    bool cond = range1.getStart() == range2.getStart();
    passIfCondTrue(cond == expected);
    std::cout << std::endl;

}

void RangeManagerTest::sameEndRange(Range &r1, Range &r2, bool expected)
{
    bool cond = r1.getEnd() == r2.getEnd();
    passIfCondTrue(cond == expected);
    std::cout << std::endl;

}



