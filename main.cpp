#include <iostream>

#include <memory>
#include <algorithm>
#include <iterator>
#include "RangeManager.h"
#include "RangeManagerTest.h"
#include "Util.h"

void test1();
void testMerge();
void testUnique();
void testToVec();
void testBasicAddDel(RangeManager &rm);


int main(int /*argc*/, char * /*argv*/[])
{
    RangeManager rm;
//    rm.add(6,8);
//    rm.add(1,4);
//    rm.add(10,15);
//    rm.add(9,12);
//    Util::printRanges(rm.get(1,5));
//    std::cout << std::endl;

    RangeManagerTest rmt;
    rmt.invalidRanges();
    rmt.validRanges();
    rmt.startEndRanges();

    return 0;
}

void testBasicAddDel(RangeManager &rm)
{
    rm.add(1,5);
    rm.add(8,10);
    rm.add(20, 19);
    rm.add(-1,0);
    rm.add(-5,-3);
    Util::printVec(rm.toVec());

    rm.del(3, 7);
    rm.del(8, 9);
    rm.del(0,0);
    rm.del(-5,-4);
    Util::printVec(rm.toVec());
}

void test1()
{
    auto r1 = std::make_unique<Range>(1, 3);
    auto r2 = std::make_unique<Range>(4, 5);
    auto r3 = std::make_unique<Range>(6, 8);
    auto r4 = std::make_unique<Range>(10, 12);

    std::vector<Range *> ranges0 = {};
    std::vector<Range *> ranges1 = { r1.get(), r2.get(), r3.get(), r4.get() };
    std::vector<Range *> ranges2 = { r1.get() };

    Util::printRanges(ranges0);
    Util::printRanges(ranges1);
    Util::printRanges(ranges2);
}

void testMerge()
{
    std::vector<int> res;
    std::vector<int> data = { 3, 3, 3, 3, 3, 3, 10 };
    std::vector<int> data2 = { 1, 2, 6 };
    std::merge(data.begin(), data.end(), data2.begin(), data2.end(), std::back_inserter(res));
    Util::printVec(res);
}

void testUnique()
{
    std::vector<int> data = { 1, 1, 3, 4, 5, 4, 10 };
    std::vector<int> res;
    auto last = std::unique(data.begin(), data.end());
    data.erase(last, data.end());
    Util::printVec(res);
}

void testToVec()
{
    Range r1(10, 12);
    Util::printVec(r1.toVec());

    Range r2(5,20);
    Util::printVec(r2.toVec());

    Range r3(0,0);
    Util::printVec(r3.toVec());
}
