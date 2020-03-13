#include "RangeManager.h"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include "Util.h"

RangeManager::RangeManager()
{

}

void RangeManager::add(int start, int end)
{
    auto range = std::make_unique<Range>(start, end);
    if (!range->valid())
    {
        std::cout << "Invalid range provided (add): ";
        std::cout << range->toStr().c_str();
        std::cout << std::endl;
        return;
    }

    std::vector<int> add = range->toVec();
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

    // TODO: copy is expensive
    ranges_ = newRanges;

    std::cout << " => "
              << Util::vecToStr(ranges_).c_str()
              << std::endl;
}

void RangeManager::del(int start, int end)
{
    auto range = std::make_unique<Range>(start, end);
    if (!range->valid())
    {
        std::cout << "Invalid range provided (del): ";
        std::cout << range->toStr().c_str();
        std::cout << std::endl;
        return;
    }

    // nothing to delete from already empty range
    if (ranges_.size() == 0)
    {
        return;
    }

    std::vector<int> remove = range->toVec();
    std::cout << "Deleting: ";
    Util::printVec(remove);

    std::vector<int> newRange;
    std::set_difference(ranges_.begin(), ranges_.end(),
                        remove.begin(), remove.end(),
                        std::inserter(newRange, newRange.begin()));

    // TODO: copy is expensive
    ranges_ = newRange;

    std::cout << " => "
              << Util::vecToStr(ranges_).c_str()
              << std::endl;

}

std::vector<Range *> RangeManager::get(int start, int end)
{
    auto range = std::make_unique<Range>(start, end);

    if (!range->valid())
    {
        std::cout << "Invalid range provided (get): ";
        std::cout << range->toStr().c_str();
        std::cout << std::endl;
        return std::vector<Range*>();
    }

    std::vector<Range*> result;
    std::vector<int> current = ranges_;

    auto notSucc = [](int x, int y)
    {
        return (y != x + 1);
    };

    // TODO: improve
    auto first = current.begin();
    auto n = std::adjacent_find(first, current.end(), notSucc);
    while (n != current.end())
    {
        result.push_back(new Range(*first, *n+1));
        first = n+1;
        n = std::adjacent_find(first, current.end(), notSucc);
    }
    n = current.end() - 1;
    result.push_back(new Range(*first, *n+1));

    return result;
}

std::vector<int> RangeManager::toVec()
{
    return ranges_;
}

