RangeManager
************

A simple class for working with integer ranges.
I have included two versions to use depending on one's needs.
Both are tested in Tests.cpp (using Catch)

RangeManager
* Allows adding, deleting and getting of Ranges
* Faster: O(ranges) -> linear time relative to the number of ranges
* Smaller cached memory footprint
* Harder to maintain: uses more custom functions

RangeManagerLinear (my first attempt)
* Same functionality
* Slower: O(values) -> linear time relative to the number of values in all the ranges
* Larger cached memory footprint
* Easier to maintain: Uses common STL functions

--- Assumptions:

Valid Range: (start, end)
             start < end, where end is exclusive
Integer-only ranges
"Delete" method as specified by question renamed to "del" to avoid collisions with c++ keyword


--- Building:

Tested on:
* C++: 14, 17
* Compilers: MSVC, GCC
* Windows, Linux

Building with Qt (MSVC):
1. Set .pro file line: "DEFINES += TEST_BUILD" as desired for main or test build
2. clean, qmake, build
3. run

Building with CLI (g++):
1. "make clean"
2. "make build" for main or "make test" for test build
3. ./rangeManager(.exe)


--- TODO:

* Optimizations
-> Copying
