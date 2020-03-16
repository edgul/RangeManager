#include "Util.h"

#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <algorithm>

namespace Util {

std::vector<int> genSequence(int start, int end)
{
    std::vector<int> v(end-start);
    std::iota(v.begin(), v.end(), start);
    return v;
}

void printVec(std::vector<int> v)
{
    std::cout << "[";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "]";
}

void printRanges(std::vector<Range> ranges)
{
    std::cout << "[";
    for (auto it = ranges.begin(); it < ranges.end(); it++)
    {
        std::cout << (*it).toStr();
        if (it != ranges.end()-1) std::cout << ", ";
    }
    std::cout << "]";
}

std::string vecToStr(std::vector<int> v)
{
    std::stringstream str;
    str << "[ ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(str, " "));
    str << "]";
    return str.str();
}

std::string rangesToStr(std::vector<Range> ranges)
{
    std::stringstream str;
    str << "[ ";
    for (auto it = ranges.begin(); it < ranges.end(); it++)
    {
        str << (*it).toStr().c_str();
        if (it != ranges.end()-1) str << ", ";
    }
    str << " ]";
    return str.str();
}

}
