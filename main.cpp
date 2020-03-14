#include <iostream>

#include <memory>
#include <algorithm>
#include <iterator>
#include "RangeManager.h"
#include "Util.h"

#define CATCH_CONFIG_MAIN // Enable this line for testing
#include "catch.hpp"

#ifdef CATCH_CONFIG_MAIN
#include "Tests.cpp"
#endif

void test1();


#ifndef CATCH_CONFIG_MAIN
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
#endif


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


