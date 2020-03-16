#include <iostream>

#include <memory>
#include <algorithm>
#include <iterator>
#include "RangeManager.h"
#include "Util.h"

#ifdef TEST_BUILD
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Tests.cpp"
#endif


#ifndef CATCH_CONFIG_MAIN
int main(int /*argc*/, char * /*argv*/[])
{
    RangeManager rm;
    rm.add(1,10);
    std::vector<Range> ranges1 = rm.get(1,10);
    std::cout << Util::rangesToStr(ranges1) << std::endl;

    rm.add(15,20);
    std::vector<Range> ranges2 = rm.get(1,20);
    std::cout << Util::rangesToStr(ranges2) << std::endl;

    rm.add(25,30);
    std::vector<Range> ranges3 = rm.get(1,30);
    std::cout << Util::rangesToStr(ranges3) << std::endl;

    rm.del(5,8);
    std::vector<Range> ranges4 = rm.get(1,30);
    std::cout << Util::rangesToStr(ranges4) << std::endl;

    return 0;
}
#endif


