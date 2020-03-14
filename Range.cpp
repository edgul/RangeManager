#include "Range.h"

#include <numeric>
#include <sstream>
#include <algorithm>
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

bool Range::valid() const
{
    return start_ < end_;
}

std::vector<int> Range::toVec() const
{
    if (!valid())
    {
        return std::vector<int>();
    }
    std::vector<int> span(end_ - start_);
    std::iota(span.begin(), span.end(), start_);
    return span;
}

std::string Range::toStr() const
{
    std::stringstream str;
    str << "(" << start_ << ", " << end_ << ")";
    return str.str();
}

int Range::getStart() const
{
    return start_;
}

int Range::getEnd() const
{
    return end_;
}

bool Range::intersects(Range &otherRange) const
{
    std::vector<int> intersection;
    const std::vector<int> thisVec = toVec();
    std::vector<int> otherVec = otherRange.toVec();
    std::set_intersection(thisVec.begin(), thisVec.end(),
                          otherVec.begin(), otherVec.end(),
                          std::back_inserter(intersection));
    return intersection.size() > 0;
}

bool Range::operator==(const Range &rhs) const
{
    return this->start_ == rhs.start_ &&
            this->end_ == rhs.end_;
}



