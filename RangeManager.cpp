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
