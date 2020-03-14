
#include <iostream>
#include <vector>
#include <numeric>
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
    Range r9(2,4);
    Range r10(-5,1);

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

    SECTION("Range intersects")
    {
        REQUIRE(r1.intersects(r2) == true);
        REQUIRE(r2.intersects(r1) == true);
        REQUIRE(r2.intersects(r2) == true);

        REQUIRE(r9.intersects(r1) == false);
        REQUIRE(r9.intersects(r2) == true);

        REQUIRE(r10.intersects(r1) == false);
        REQUIRE(r1.intersects(r10) == false);
        REQUIRE(r10.intersects(r3) == true);
        REQUIRE(r3.intersects(r10) == true);
    }
}

TEST_CASE("RangeManager Add/Del", "[RangeManager Add/Del]")
{
    RangeManager rm;

    std::vector<int> vec;
    SECTION("Default Range Manager is empty")
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

    SECTION("Add non-overlapping sets")
    {
        vec = {1,2,3,4,8,9};
        rm.add(1,5);
        rm.add(8,10);
        REQUIRE(rm.toVec() == vec);

        std::vector<int> v1{15,16,17};
        vec.insert(std::end(vec), std::begin(v1), std::end(v1));
        rm.add(15,18);
        REQUIRE(rm.toVec() == vec);

        std::vector<int> v2{100,101,102,103,104,105,106,107,108,109};
        vec.insert(std::end(vec), std::begin(v2), std::end(v2));
        rm.add(100,110);
        REQUIRE(rm.toVec() == vec);

        SECTION("Doesn't add invalid range")
        {
            rm.add(20, 19);
            REQUIRE(rm.toVec() == vec);
        }

        SECTION("Keeps order")
        {
            vec.insert(vec.begin(), -1);
            rm.add(-1,0);
            REQUIRE(rm.toVec() == vec);

            vec.insert(vec.begin(), -4);
            vec.insert(vec.begin(), -5);
            rm.add(-5,-3);
            REQUIRE(rm.toVec() == vec);

            auto it = std::find(vec.begin(), vec.end(), 17)+1;
            std::vector<int> middleVector{50,51,52,53,54,55};
            vec.insert(it, std::begin(middleVector), std::end(middleVector));
            rm.add(50,56);
            REQUIRE(rm.toVec() == vec);
        }
    }
}

TEST_CASE("RangeManager Get", "[RangeManager Get]")
{
    RangeManager rm;
    rm.add(1,10);
    SECTION("Get more than set")
    {
        std::vector<Range*> r = rm.get(1,30);
        REQUIRE(*(rm.get(1,10).at(0)) == Range(1,10));
        REQUIRE(rm.get(1,10).at(0)->getStart() == 1);
        REQUIRE(rm.get(1,10).at(0)->getEnd() == 10);
        REQUIRE(rm.get(1,10).at(0)->toVec() == std::vector<int>{1,2,3,4,5,6,7,8,9});
    }

    rm.add(20,30);
    SECTION("Get all of two ranges")
    {
        std::vector<Range*> r = rm.get(1,30);
        REQUIRE(r.size() == 2);

        REQUIRE(*(r.at(0)) == Range(1,10));
        REQUIRE(r.at(0)->getStart() == 1);
        REQUIRE(r.at(0)->getEnd() == 10);
        REQUIRE(r.at(0)->toVec() == std::vector<int>{1,2,3,4,5,6,7,8,9});

        REQUIRE(*(r.at(1)) == Range(20,30));
        REQUIRE(r.at(1)->getStart() == 20);
        REQUIRE(r.at(1)->getEnd() == 30);
        REQUIRE(r.at(1)->toVec() == std::vector<int>{20,21,22,23,24,25,26,27,28,29});

    }

    rm.add(40,50);
    SECTION("Get only two of three ") // TODO: add more tests here
    {
        std::vector<Range*> r = rm.get(1,30);
        REQUIRE(r.size() == 2);

        REQUIRE(*(r.at(1)) == Range(20,30));
        REQUIRE(r.at(1)->getStart() == 20);
        REQUIRE(r.at(1)->getEnd() == 30);
        REQUIRE(r.at(1)->toVec() == std::vector<int>{20,21,22,23,24,25,26,27,28,29});
    }
}

