
#include <iostream>
#include <vector>
#include "Range.h"
#include "RangeManager.h"
#include "catch.hpp"

TEST_CASE( "Range test", "[Range]" )
{
    Range r1(1,2);
    Range r2(1,4);
    Range r3(0, 1000000);
    Range r4(-10, 10);
    Range r5(100, 100000);
    Range r6(1000, 100000);
    Range r7(-1000, 1000);
    Range r8(-10000, 10000);

    Range rInvalid0(0,0);
    Range rInvalid1(1, -1);
    Range rInvalid2(0,-10000);
;

    SECTION("Ranges init")
    {
        REQUIRE(r1.getStart() == 1);
        REQUIRE(r1.getEnd() == 2);
        REQUIRE(r2.getStart() == 1);
        REQUIRE(r2.getEnd() == 4);
        REQUIRE(r3.getStart() == 0);
        REQUIRE(r3.getEnd() == 1000000);
        REQUIRE(r4.getStart() == -10);
        REQUIRE(r4.getEnd() == 10);

        REQUIRE(rInvalid0.getStart() == 0);
        REQUIRE(rInvalid0.getEnd() == 0);
        REQUIRE(rInvalid1.getStart() == 1);
        REQUIRE(rInvalid1.getEnd() == -1);
    }

    SECTION("Ranges validity")
    {
        REQUIRE(r1.valid() == true);
        REQUIRE(r2.valid() == true);
        REQUIRE(r3.valid() == true);
        REQUIRE(r4.valid() == true);
        REQUIRE(r5.valid() == true);
        REQUIRE(r6.valid() == true);
        REQUIRE(r7.valid() == true);
        REQUIRE(r8.valid() == true);

        REQUIRE(rInvalid0.valid() == false);
        REQUIRE(rInvalid1.valid() == false);
        REQUIRE(rInvalid2.valid() == false);
    }

    SECTION("Range Clearing")
    {
        r1       .clear();
        r2       .clear();
        r3       .clear();
        r4       .clear();
        rInvalid0.clear();
        rInvalid1.clear();

        REQUIRE(r1.valid() == false);
        REQUIRE(r2.valid() == false);
        REQUIRE(r4.valid() == false);
        REQUIRE(rInvalid0.valid() == false);
        REQUIRE(rInvalid1.valid() == false);
    }

}

TEST_CASE("RangeManager Add/Del", "[RangeManager Add/Del]")
{
    RangeManager rm;

    std::vector<int> vec;
    SECTION("Default Range Manager")
    {
        REQUIRE(rm.toVec() == vec);
    }

    rm.add(1,5);
    vec = {1,2,3,4};
    REQUIRE(rm.toVec() == vec);

    SECTION("Delete all one at a time ")
    {
        vec.pop_back();
        rm.del(4,5);
        REQUIRE(rm.toVec() == vec);

        vec.pop_back();
        rm.del(3,4);
        REQUIRE(rm.toVec() == vec);

        vec.pop_back();
        rm.del(2,3);
        REQUIRE(rm.toVec() == vec);

        // delete nothing is same
        rm.del(2,3);
        REQUIRE(rm.toVec() == vec);

        vec.pop_back();
        rm.del(1,2);
        REQUIRE(rm.toVec() == vec);
    }
}
