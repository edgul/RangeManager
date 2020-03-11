#include <iostream>

#include <memory>
#include <algorithm>
#include <iterator>
#include "RangeManager.h"
#include "Util.h"

void test1(RangeManager &rm);
void testMerge();
void testUnique();
void testToVec();



int main(int /*argc*/, char * /*argv*/[])
{
    std::cout << "Hello world" << std::endl;

    RangeManager rm;

    std::vector<int> data = { 1, 2, 3, 4, 5, 4, 10 };
    std::vector<int> data2 = { 1, 2, 6 };

    rm.add(3,5);
    rm.add(8,10);
    // rm.printRanges();

    return 0;
}

void test1(RangeManager &rm)
{
    auto r1 = std::make_unique<Range>(1, 3);
    auto r2 = std::make_unique<Range>(4, 5);
    auto r3 = std::make_unique<Range>(6, 8);
    auto r4 = std::make_unique<Range>(10, 12);

    std::vector<Range *> ranges0 = {};
    std::vector<Range *> ranges1 = { r1.get(), r2.get(), r3.get(), r4.get() };
    std::vector<Range *> ranges2 = { r1.get() };

    rm.printRanges(ranges0);
    rm.printRanges(ranges1);
    rm.printRanges(ranges2);
}

void testMerge()
{
    std::vector<int> res;
    std::vector<int> data = { 3, 3, 3, 3, 3, 3, 10 };
    std::vector<int> data2 = { 1, 2, 6 };
    std::merge(data.begin(), data.end(), data2.begin(), data2.end(), std::back_inserter(res));
    Util::print(res);
}

void testUnique()
{
    std::vector<int> data = { 1, 1, 3, 4, 5, 4, 10 };
    std::vector<int> res;
    auto last = std::unique(data.begin(), data.end());
    data.erase(last, data.end());
    Util::print(res);
}

void testToVec()
{
    Range r1(10, 12);
    Util::print(r1.toVec());

    Range r2(5,20);
    Util::print(r2.toVec());

    Range r3(0,0);
    Util::print(r3.toVec());
}
