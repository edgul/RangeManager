#include "RangeManager.h"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include "Util.h"

RangeManager::RangeManager()
{

}

void RangeManager::clear()
{
    ranges_.clear();
}

void RangeManager::add(int start, int end)
{
    Range newRange(start, end);
    if (!newRange.valid())
    {
        return;
    }

    std::vector<Range> ranges;
    bool newRangeAdded = false;
    for (auto const& range : ranges_)
    {
        if (newRangeAdded)
        {
            ranges.push_back(range);
        }
        else
        {
            if (range.willMergeWith(newRange))
            {
                newRange.mergeWith(range);
            }
            else if (range.start() < newRange.start())
            {
                ranges.push_back(range);
            }
            else
            {
                ranges.push_back(newRange);
                ranges.push_back(range);
                newRangeAdded = true;
            }
        }
    }

    if(!newRangeAdded)
    {
        ranges.push_back(newRange);
    }

    ranges_ = ranges;
}

void RangeManager::del(int start, int end)
{
    Range delRange(start, end);
    if (!delRange.valid())
    {
        return;
    }

    std::vector<Range> ranges;
    for (auto & range : ranges_)
    {
        if (range.intersects(delRange))
        {
            std::vector<Range> remainderRanges = range.del(delRange);
            ranges.insert(ranges.end(), remainderRanges.begin(), remainderRanges.end());
        }
        else
        {
            ranges.push_back(range);
        }
    }

    ranges_ = ranges;
}

std::vector<int> RangeManager::toVec() const
{
    std::vector<int> ranges;
    for (auto const& range : ranges_)
    {
        std::vector<int> curRange = range.toVec();
        ranges.insert(ranges.end(), curRange.begin(), curRange.end());
    }
    return ranges;
}

std::vector<Range> RangeManager::get(int start, int end) const
{
    Range getRange(start, end);
    if (!getRange.valid())
    {
        std::vector<Range>();
    }

    std::vector<Range> result;
    for (auto const& range : ranges_)
    {
        if (range.intersects(getRange))
        {
            result.push_back(range);
        }
    }

    return result;
}

void RangeManager::clearLinear()
{
    rangesLinear_.clear();
}

void RangeManager::addLinear(int start, int end)
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
               rangesLinear_.begin(), rangesLinear_.end(),
               std::back_inserter(newRanges));

    // remove duplicates
    auto last = std::unique(newRanges.begin(), newRanges.end());
    newRanges.erase(last, newRanges.end());

    rangesLinear_ = newRanges;

    std::cout << " => "
              << Util::vecToStr(rangesLinear_).c_str()
              << std::endl;
}

std::vector<Range> RangeManager::getLinear(int start, int end) const
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
    std::vector<int> current = rangesLinear_;

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

void RangeManager::delLinear(int start, int end)
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
    if (rangesLinear_.size() == 0)
    {
        return;
    }

    std::vector<int> remove = range.toVec();
    std::cout << "Deleting: ";
    Util::printVec(remove);

    std::vector<int> newRange;
    std::set_difference(rangesLinear_.begin(), rangesLinear_.end(),
                        remove.begin(), remove.end(),
                        std::inserter(newRange, newRange.begin()));

    rangesLinear_ = newRange;

    std::cout << " => "
              << Util::vecToStr(rangesLinear_).c_str()
              << std::endl;
}

std::vector<int> RangeManager::toVecLinear() const
{
    return rangesLinear_;
}

