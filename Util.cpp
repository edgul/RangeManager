#include "Util.h"

#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

namespace Util {

std::vector<int> genSequence(int start, int end)
{
    int i = start;
    auto f = [&]() {
        return i++;
    };

    std::vector<int> v(end-start);
    std::generate(v.begin(), v.end(), f);
    return v;
}

void printVec(std::vector<int> v)
{
    std::cout << "[ ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "]";
}

void printRanges(std::vector<Range *> ranges)
{
    std::cout << "[";
    for (auto it = ranges.begin(); it < ranges.end(); it++)
    {
        std::cout << (*it)->toStr();
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

std::string rangesToStr(std::vector<Range *> ranges)
{
    std::stringstream str;
    str << "[ ";
    for (auto it = ranges.begin(); it < ranges.end(); it++)
    {
        str << (*it)->toStr().c_str();
        if (it != ranges.end()-1) str << ", ";
    }
    str << "]";
    return str.str();
}

}
