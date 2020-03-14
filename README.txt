
Assumptions:
* Valid Range: start < end
* Integer-only ranges
* "Delete" method as specified by question renamed to "del" to avoid collisions with c++ keyword

Building:
* C++: 14 or 17
* Compilers: MSVC or GCC

Uses Testing Framework: Catch
* For test/main build un/comment line: #define CATCH_CONFIG_MAIN 

// TODO:
* Add more testing
* Optimizations
-> Performance (Speed and Footprint)
-> Leaks
* Measure complexity
* Internal Representation?
* Debug switch for live printing
