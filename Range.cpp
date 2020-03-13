#include "Range.h"

#include <numeric>
#include <sstream>
#include "Util.h"

Range::Range(int start, int end) : start_(start), end_(end)
{

}

Range::~Range()
{
    // TODO: optimize
    // std::cout << "Range being destroyed: ";
    // print();
    // std::cout << std::endl;
}

void Range::clear()
{
    start_ = 0;
    end_ = 0;
}

bool Range::valid()
{
    return start_ < end_;
}

std::vector<int> Range::toVec()
{
    if (!valid())
    {
        return std::vector<int>();
    }
    std::vector<int> span(end_ - start_);
    std::iota(span.begin(), span.end(), start_);
    return span;
}

std::string Range::toStr()
{
    std::stringstream str;
    str << "(" << start_ << ", " << end_ << ")";
    return str.str();
}

int Range::getStart()
{
    return start_;
}

int Range::getEnd()
{
    return end_;
}
