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

void Range::setStart(int start)
{
    start_ = start;
}

void Range::setEnd(int end)
{
    end_ = end;
}

int Range::getStart() const
{
    return start_;
}

int Range::getEnd() const
{
    return end_;
}

bool Range::contains(int value) const
{
    return (value >= start_ && value < end_);
}

bool Range::lower(int value) const
{
    return (value < start_);
}

bool Range::higher(int value) const
{
    return (value >= end_);
}

bool Range::hasHigher(const Range &other) const
{
    for (int i = other.getStart(); i < other.getEnd(); i++)
    {
        if (higher(i)) return true;
    }
    return false;
}

bool Range::hasLower(const Range &other) const
{
    for (int i = other.getStart(); i < other.getEnd(); i++)
    {
        if (lower(i)) return true;
    }
    return false;
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

    for (int i = smallerRange.getStart(); i < smallerRange.getEnd(); i++)
    {
        if (biggerRange.contains(i))
        {
            inter = true;
            break;
        }
    }
    return inter;
}

bool Range::operator==(const Range &rhs) const
{
    return this->start_ == rhs.start_ &&
            this->end_ == rhs.end_;
}

int Range::size() const
{
    if (!valid()) return 0;

    return end_ - start_;
}

std::vector<Range> Range::add(const Range &other) const
{
    Range thisRange = Range(start_, end_);

    // one range is empty
    if (size() == 0)
    {
        return std::vector<Range>{other};
    }
    else if (other.size() == 0)
    {
        return std::vector<Range>{thisRange};
    }

    std::vector<Range> result;
    if (contains(other.getStart())) // overlap other start-bounded
    {
        if (contains(other.getEnd()-1)) // same size or this is larger
        {
            result.push_back(thisRange);
        }
        else // other higher
        {
            Range newRange(thisRange.getStart(), other.getEnd());
            result.push_back(newRange);
        }
    }
    else if (contains(other.getEnd()-1)) // overlap other end-bounded
    {
        Range newRange(other.getStart(), thisRange.getEnd());
        result.push_back(newRange);
    }
    else if (end_ == other.getStart()) // end-to-end - other higher
    {
        Range newRange(thisRange.getStart(), other.getEnd());
        result.push_back(newRange);
    }
    else if (start_ == other.getEnd()) // end-to-end - other lower
    {
        Range newRange(other.getStart(), thisRange.getEnd());
        result.push_back(newRange);
    }
    else if (start_ > other.getStart()) // no overlap - other lower
    {
        result.push_back(other);
        result.push_back(thisRange);
    }
    else if (start_ < other.getStart()) // no overlap - other higher
    {
        result.push_back(thisRange);
        result.push_back(other);
    }
    else
    {
        assert(false);
    }

    return result;
}

Range Range::shorter(const Range &r1, const Range &r2)
{
    return (r1.size() >= r2.size()) ? r2 : r1;
}

Range Range::longer(const Range &r1, const Range &r2)
{
    return (r1.size() >= r2.size()) ? r1 : r2;
}



