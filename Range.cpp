#include "Range.h"

#include <numeric>
#include <sstream>
#include <algorithm>
#include <cassert>
#include "Util.h"

Range::Range(int start, int end) : start_(start), end_(end)
{

}

Range::~Range()
{
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

int Range::size() const
{
    if (!valid()) return 0;
    return end_ - start_;
}

int Range::start() const
{
    return start_;
}

int Range::end() const
{
    return end_;
}

bool Range::contains(int value) const
{
    return (value >= start_ && value < end_);
}

bool Range::intersects(const Range &otherRange) const
{
    bool inter = false;

    if (size() == 0 || otherRange.size() == 0)
    {
        return false;
    }

    Range smallerRange = shorter(Range(start_,end_), otherRange);
    Range biggerRange = longer(Range(start_,end_), otherRange);

    for (int i = smallerRange.start(); i < smallerRange.end(); i++)
    {
        if (biggerRange.contains(i))
        {
            inter = true;
            break;
        }
    }
    return inter;
}

bool Range::willMergeWith(const Range &other) const
{
    if (size() == 0 || other.size() == 0)
    {
        return true;
    }

    return intersects(other) || start_ == other.end() || end_ == other.start();
}

void Range::mergeWith(const Range &other)
{
    // one range is empty
    if (size() == 0)
    {
        start_ = other.start();
        end_ = other.end();
        return;
    }
    else if (other.size() == 0)
    {
        return;
    }

    std::vector<Range> result;
    if (contains(other.start())) // overlap - other start-bounded
    {
        if (!contains(other.end()-1)) // other has higher end
        {
            end_ = other.end();
        }
        // else other is contained or equal to "this"
    }
    else if (contains(other.end()-1)) // overlap other end-bounded
    {
        start_ = other.start();
    }
    else if (end_ == other.start()) // end-to-end - other higher
    {
        end_ = other.end();
    }
    else if (start_ == other.end()) // end-to-end - other lower
    {
        start_ = other.start();
    }
    else // other contains "this"
    {
        start_ = other.start();
        end_ = other.end();
    }
}

std::vector<Range> Range::del(const Range &delRange)
{
    if (!delRange.valid() || !intersects(delRange))
    {
        return std::vector<Range>{ Range(start_, end_) };
    }

    std::vector<Range> ranges;
    if (delRange.contains(start_)) // overlap
    {
        if (delRange.contains(end_- 1)) // delRange contains "this" or equal
        {
            return std::vector<Range>();
        }
        else // delRange is lower than "this"
        {
            Range newRange(delRange.end(), end_);
            ranges.push_back(newRange);
        }
    }
    else if (delRange.contains(end_)) // overlap -- delRange higher than "this"
    {
        Range newRange(start_, delRange.start());
        ranges.push_back(newRange);
    }
    else // delRange within "this"
    {
        Range newRange1(start_, delRange.start());
        Range newRange2(delRange.end(), end_);
        ranges.push_back(newRange1);
        ranges.push_back(newRange2);
    }

    return ranges;
}

Range Range::shorter(const Range &r1, const Range &r2) const
{
    return (r1.size() >= r2.size()) ? r2 : r1;
}

Range Range::longer(const Range &r1, const Range &r2) const
{
    return (r1.size() >= r2.size()) ? r1 : r2;
}

bool Range::operator==(const Range &rhs) const
{
    return this->start_ == rhs.start_ &&
            this->end_ == rhs.end_;
}



