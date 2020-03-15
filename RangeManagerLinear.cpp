#include "RangeManagerLinear.h"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include "Util.h"

RangeManagerLinear::RangeManagerLinear()
{

}

void RangeManagerLinear::clear()
{
    ranges_.clear();
}

void RangeManagerLinear::add(int start, int end)
{
    Range range(start, end);
    if (!range.valid())
    {
        std::cout << "Invalid range provided (add): ";
        std::cout << range.toStr().c_str();
        std::cout << std::endl;
        return;
    }

    std::vector<int> add = range.toVec();
    std::cout << "Adding: ";
    Util::printVec(add);

    // merge (keeps sorted)
    std::vector<int> newRanges;
    std::merge(add.begin(), add.end(),
               ranges_.begin(), ranges_.end(),
               std::back_inserter(newRanges));

    // remove duplicates
    auto last = std::unique(newRanges.begin(), newRanges.end());
    newRanges.erase(last, newRanges.end());

    ranges_ = newRanges;

    std::cout << " => "
              << Util::vecToStr(ranges_).c_str()
              << std::endl;
}

void RangeManagerLinear::del(int start, int end)
{

    Range range(start, end);
    if (!range.valid())
    {
        std::cout << "Invalid range provided (del): ";
        std::cout << range.toStr().c_str();
        std::cout << std::endl;
        return;
    }

    // nothing to delete from already empty range
    if (ranges_.size() == 0)
    {
        return;
    }

    std::vector<int> remove = range.toVec();
    std::cout << "Deleting: ";
    Util::printVec(remove);

    std::vector<int> newRange;
    std::set_difference(ranges_.begin(), ranges_.end(),
                        remove.begin(), remove.end(),
                        std::inserter(newRange, newRange.begin()));

    ranges_ = newRange;

    std::cout << " => "
              << Util::vecToStr(ranges_).c_str()
              << std::endl;



}

std::vector<Range> RangeManagerLinear::get(int start, int end) const
{
    Range range(start, end);

    if (!range.valid())
    {
        std::cout << "Invalid range provided (get): ";
        std::cout << range.toStr().c_str();
        std::cout << std::endl;
        return std::vector<Range>();
    }

    std::vector<Range> result;
    std::vector<int> current = ranges_;

    auto notSucc = [](int x, int y)
    {
        return (y != x + 1);
    };

    auto first = current.begin();
    auto n = std::adjacent_find(first, current.end(), notSucc);
    while (n != current.end())
    {
        Range r =  Range(*first, *n+1);
        Range r2 = Range(start,end);
        if (r.intersects(r2))
        {
            result.push_back(r);
        }
        first = n+1;
        n = std::adjacent_find(first, current.end(), notSucc);
    }
    n = current.end() - 1;
    Range r = Range(*first, *n+1);
    Range r2 = Range(start,end);
    if (r.intersects(r2))
    {
        result.push_back(r);
    }

    return result;
}

std::vector<int> RangeManagerLinear::toVec() const
{
    return ranges_;
}
