RangeManager
************
A simple class for working with integer ranges.
Includes tests (Catch)

--- Assumptions:

Valid Range: (start, end)
             start < end, where end is exclusive
Integer-only ranges
"Delete" method as specified by question renamed to "del" to avoid collisions with c++ keyword


--- Building:

C++: 14, 17
Compilers: MSVC, GCC

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
-> Performance (Speed and Footprint)
-> Leaks
* Measure complexity
* Internal Representation?
* Debug switch for live printing
* Test on Linux
