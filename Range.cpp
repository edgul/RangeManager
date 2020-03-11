#include "Range.h"

#include <iostream>
#include <numeric>
#include "Util.h"

Range::Range(int start, int end) : start_(start), end_(end)
{

}

Range::~Range()
{
    std::cout << "Range being deleted: ";
    print();
    std::cout << std::endl;
}

void Range::setStart(int start)
{
    start_ = start;
}

void Range::setEnd(int end)
{
    end_ = end;
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

void Range::print()
{
    std::cout << "(" << start_ << ", " << end_ << ")";
}

std::vector<int> Range::toVec()
{
    if (!valid())
    {
        return std::vector<int>();
    }
    std::vector<int> span(end_ - start_);
    std::iota(span.begin(), span.end(), start_);
    Util::print(span);
    return span;
}
