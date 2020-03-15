
#include <iostream>
#include <vector>
#include <numeric>
#include "Range.h"
#include "RangeManager.h"
#include "RangeManagerLinear.h"
#include "Util.h"
#include "catch.hpp"

void compareRange(const Range &range1, const Range &range2);
void rangeManagerGet(IRangeManager &rm);
void rangeManagerAddDel(IRangeManager &rm);


TEST_CASE( "Util test", "[Util]")
{
    REQUIRE(Util::genSequence(1,10) == std::vector<int>{1,2,3,4,5,6,7,8,9});
    REQUIRE(Util::genSequence(-10,0) == std::vector<int>{-10,-9,-8,-7,-6,-5,-4,-3,-2,-1});
    REQUIRE(Util::genSequence(-10,10) == std::vector<int>{-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9});
}

TEST_CASE("RangeManager Add/Del", "[RangeManager Add/Del]")
{
    RangeManager rm;
    rangeManagerAddDel(rm);
}

TEST_CASE("RangeManagerLinear Add/Del", "[RangeMangerLinear Add/Del]")
{
    RangeManagerLinear rml;
    rangeManagerAddDel(rml);
}

TEST_CASE("RangeManager Get", "[RangeManager Get]")
{
    RangeManager rm;
    rangeManagerGet(rm);
}

TEST_CASE("RangeManagerLinear Get", "[RangeMangerLinear Get}")
{
    RangeManagerLinear rml;
    rangeManagerGet(rml);
}

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
        REQUIRE(r1.start() == 1);
        REQUIRE(r1.end() == 2);
        REQUIRE(r2.start() == 1);
        REQUIRE(r2.end() == 4);
        REQUIRE(r3.start() == 0);
        REQUIRE(r3.end() == 1000000);
        REQUIRE(r4.start() == -10);
        REQUIRE(r4.end() == 10);

        REQUIRE(rInvalid0.start() == 0);
        REQUIRE(rInvalid0.end() == 0);
        REQUIRE(rInvalid1.start() == 1);
        REQUIRE(rInvalid1.end() == -1);
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

    SECTION("Range Contains")
    {
        for (int i : Util::genSequence(-1000,0))
        {
            REQUIRE(r2.contains(i) == false);
        }
        REQUIRE(r2.contains(0) == false);
        REQUIRE(r2.contains(1) == true);
        REQUIRE(r2.contains(2) == true);
        REQUIRE(r2.contains(3) == true);
        REQUIRE(r2.contains(4) == false);
        for (int i : Util::genSequence(5, 1000))
        {
            REQUIRE(r2.contains(i) == false);
        }

        for (int i : Util::genSequence(-1000, -6))
        {
            REQUIRE(r10.contains(i) == false);
        }
        REQUIRE(r10.contains(-6) == false);
        REQUIRE(r10.contains(-5) == true);
        REQUIRE(r10.contains(-4) == true);
        REQUIRE(r10.contains(-3) == true);
        REQUIRE(r10.contains(-2) == true);
        REQUIRE(r10.contains(-1) == true);
        REQUIRE(r10.contains(0) == true);
        REQUIRE(r10.contains(1) == false);
        for (int i : Util::genSequence(2, 1000))
        {
            REQUIRE(r10.contains(i) == false);
        }

        REQUIRE(rInvalid0.contains(-1) == false);
        REQUIRE(rInvalid0.contains(0) == false);
        REQUIRE(rInvalid0.contains(1) == false);
    }

    SECTION("Range intersects")
    {
        REQUIRE(r1.intersects(r2) == true);
        REQUIRE(r2.intersects(r1) == true);
        REQUIRE(r2.intersects(r2) == true);

        REQUIRE(r9.intersects(r1) == false);
        REQUIRE(r1.intersects(r9) == false);
        REQUIRE(r9.intersects(r2) == true);
        REQUIRE(r2.intersects(r9) == true);

        REQUIRE(r10.intersects(r1) == false);
        REQUIRE(r1.intersects(r10) == false);
        REQUIRE(r10.intersects(r3) == true);
        REQUIRE(r3.intersects(r10) == true);
        REQUIRE(r10.intersects(r2) == false);
        REQUIRE(r2.intersects(r10) == false);
        REQUIRE(r10.intersects(rInvalid0) == false);
        REQUIRE(rInvalid0.intersects(r10) == false);
        REQUIRE(r3.intersects(rInvalid0) == false);
        REQUIRE(rInvalid0.intersects(r3) == false);

        REQUIRE(r1.intersects(r3) == true);
        REQUIRE(r3.intersects(r1) == true);
        REQUIRE(r2.intersects(r3) == true);
        REQUIRE(r3.intersects(r2) == true);
    }

    SECTION("Range toVec")
    {
        REQUIRE(r1.toVec() == std::vector<int>{1});
        REQUIRE(r2.toVec() == std::vector<int>{1,2,3});
        REQUIRE(r3.toVec() == Util::genSequence(0, 1000000));
        REQUIRE(r4.toVec() == Util::genSequence(-10, 10));
        REQUIRE(r7.toVec() == Util::genSequence(-1000, 1000));
        REQUIRE(r8.toVec() == Util::genSequence(-10000, 10000));
    }

    SECTION("Range will merge with")
    {
        Range r0(-3,1);
        Range r1(1,10);
        Range r2(10,20);
        Range r3(15,20);
        Range r4(11, 20);
        Range r5(-3, 0);
        Range r6(-3,5);
        Range r7(8,12);
        REQUIRE(r1.willMergeWith(r0) == true); // end to end
        REQUIRE(r0.willMergeWith(r1) == true);
        REQUIRE(r1.willMergeWith(r2) == true); // end to end
        REQUIRE(r2.willMergeWith(r1) == true);
        REQUIRE(r1.willMergeWith(r3) == false);
        REQUIRE(r3.willMergeWith(r1) == false);
        REQUIRE(r1.willMergeWith(r4) == false);
        REQUIRE(r4.willMergeWith(r1) == false);
        REQUIRE(r2.willMergeWith(r3) == true);
        REQUIRE(r3.willMergeWith(r2) == true);
        REQUIRE(r1.willMergeWith(r5) == false);
        REQUIRE(r5.willMergeWith(r1) == false);
        REQUIRE(r1.willMergeWith(r6) == true);
        REQUIRE(r6.willMergeWith(r1) == true);
        REQUIRE(r1.willMergeWith(r7) == true);
        REQUIRE(r7.willMergeWith(r1) == true);
    }

    SECTION("Range mergeWith")
    {
        Range r1(1,10);
        Range r2(5,6);
        r1.mergeWith(r2);
        REQUIRE(r1 == Range(1,10));

        r1 = Range(1,10);
        Range r3(-3, 2);
        r1.mergeWith(r3);
        REQUIRE(r1 == Range(-3, 10));

        r1 = Range(1,10);
        Range r4(8, 12);
        r1.mergeWith(r4);
        REQUIRE(r1 == Range(1,12));

        r1 = Range(1,10);
        Range r5(-5, 15);
        r1.mergeWith(r5);
        REQUIRE(r1 == r5);
    }

    SECTION("Range del")
    {
        Range r1(1, 10);
        Range r2(-1, 1);
        Range r3(10, 12);
        Range r4(0,5);
        Range r5(5,11);
        Range r6(5,7);
        REQUIRE(r1.del(r2) == std::vector<Range>{r1});
        REQUIRE(r1.del(r3) == std::vector<Range>{r1});
        REQUIRE(r1.del(r4) == std::vector<Range>{ Range(5,10) });
        REQUIRE(r1.del(r5) == std::vector<Range>{ Range(1,5) });
        REQUIRE(r1.del(r6) == std::vector<Range>{ Range(1,5), Range(7,10) });
    }

    SECTION("Range size")
    {
        Range r1(1,10);
        REQUIRE(r1.size() == 9);

        Range r2(2,2);
        REQUIRE(r2.size() == 0);

        Range r3(2,1);
        REQUIRE(r3.size() == 0);

        Range r4(-5, 10);
        REQUIRE(r4.size() == 15);
    }
}

void compareRange(const Range &range1, const Range &range2)
{
    REQUIRE(range1 == range2);
    REQUIRE(range1.start() == range1.start());
    REQUIRE(range1.end() == range2.end());
    REQUIRE(range1.toVec() == range2.toVec());
}

void rangeManagerGet(IRangeManager &rm)
{
    rm.add(1,10);
    SECTION("Get more than set")
    {
        std::vector<Range> r = rm.get(1,30);
        REQUIRE((rm.get(1,10).at(0)) == Range(1,10));
        REQUIRE(rm.get(1,10).at(0).start() == 1);
        REQUIRE(rm.get(1,10).at(0).end() == 10);
        REQUIRE(rm.get(1,10).at(0).toVec() == std::vector<int>{1,2,3,4,5,6,7,8,9});
    }

    rm.add(20,30);
    SECTION("Get all of two ranges")
    {
        std::vector<Range> r = rm.get(1,30);
        REQUIRE(r.size() == 2);

        compareRange((r.at(0)), Range(1,10));
        compareRange((r.at(1)), Range(20,30));
    }

    rm.add(40,50);
    SECTION("Get first two of three by whole overlap ")
    {
        std::vector<Range> r = rm.get(1,30);
        REQUIRE(r.size() == 2);

        compareRange((r.at(0)), Range(1,10));
        compareRange((r.at(1)), Range(20,30));
    }
    SECTION("Get second two of three by whole overlap")
    {
        std::vector<Range> r = rm.get(10, 50);
        REQUIRE(r.size() == 2);

        compareRange((r.at(0)), Range(20,30));
        compareRange((r.at(1)), Range(40,50));
    }
    SECTION("Get first two of three by partial overlap ")
    {
        std::vector<Range> r = rm.get(5,25);
        REQUIRE(r.size() == 2);

        compareRange((r.at(0)), Range(1,10));
        compareRange((r.at(1)), Range(20,30));
    }
    SECTION("Get second two of three by partial overlap")
    {
        std::vector<Range> r = rm.get(25, 45);
        REQUIRE(r.size() == 2);
        compareRange((r.at(0)), Range(20,30));
        compareRange((r.at(1)), Range(40,50));
    }

    SECTION("Get middle of three by whole overlap")
    {
        std::vector<Range> r = rm.get(20, 30);
        REQUIRE(r.size() == 1);
        compareRange((r.at(0)), Range(20,30));
    }
    SECTION("Get middle of three by whole overlap bottom excess")
    {
        std::vector<Range> r = rm.get(15, 30);
        REQUIRE(r.size() == 1);
        compareRange((r.at(0)), Range(20,30));
    }
    SECTION("Get middle of three by whole overlap top excess")
    {
        std::vector<Range> r = rm.get(20, 34);
        REQUIRE(r.size() == 1);
        compareRange((r.at(0)), Range(20,30));
    }

    SECTION("Get bottom miss")
    {
        std::vector<Range> r = rm.get(-10, 1);
        REQUIRE(r.size() == 0);
    }
    SECTION("Get mid miss 1")
    {
        std::vector<Range> r = rm.get(15,18);
        REQUIRE(r.size() == 0);
    }
    SECTION("Get mid miss 2")
    {
        std::vector<Range> r = rm.get(30,40);
        REQUIRE(r.size() == 0);
    }
    SECTION("Get top miss")
    {
        std::vector<Range> r = rm.get(50,55);
        REQUIRE(r.size() == 0);
    }
}

void rangeManagerAddDel(IRangeManager &rm)
{
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

    rm.clear();
    rm.add(1,30);
    REQUIRE(rm.toVec() == Util::genSequence(1,30));

    SECTION("Del from terminals")
    {

        rm.del(25,30);
        SECTION("Del from end exact")
        {
            std::vector<Range> v = rm.get(1,30);
            REQUIRE(v.size() == 1);
            compareRange((v.at(0)), Range(1,25));
        }

        rm.del(20,30);
        SECTION("Del from end excess")
        {
            std::vector<Range> v = rm.get(1,30);
            REQUIRE(v.size() == 1);
            compareRange((v.at(0)), Range(1,20));
        }

        rm.del(1,5);
        SECTION("Del from beginning exact")
        {
            std::vector<Range> v = rm.get(1,30);
            REQUIRE(v.size() == 1);
            compareRange((v.at(0)), Range(5,20));
        }

        rm.del(1,10);
        SECTION("Del from beginning excess")
        {
            std::vector<Range> v = rm.get(1,30);
            REQUIRE(v.size() == 1);
            compareRange((v.at(0)), Range(10,20));
        }
    }
    SECTION("Del from middle")
    {
        rm.del(15,16);

        SECTION("Del middle single")
        {
            std::vector<Range> v = rm.get(1,30);
            REQUIRE(v.size() == 2);
            compareRange((v.at(0)), Range(1,15));
            compareRange((v.at(1)), Range(16,30));
        }

        rm.del(22,24);
        SECTION("Del middle two")
        {
            std::vector<Range> v = rm.get(1,30);
            REQUIRE(v.size() == 3);
            compareRange((v.at(0)), Range(1,15));
            compareRange((v.at(1)), Range(16,22));
            compareRange((v.at(2)), Range(24,30));
        }

        rm.del(10,13);
        SECTION("Del middle three")
        {
            std::vector<Range> v = rm.get(1,30);
            REQUIRE(v.size() == 4);
            compareRange((v.at(0)), Range(1,10));
            compareRange((v.at(1)), Range(13,15));
            compareRange((v.at(2)), Range(16,22));
            compareRange((v.at(3)), Range(24,30));
        }
    }
}
