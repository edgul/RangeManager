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

    return 0;
}
#endif


