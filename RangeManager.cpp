#include "RangeManager.h"

#include <iostream>
#include <algorithm>
#include "Util.h"

bool notSucc(int x, int y)
{
    return (y != x + 1);
}

RangeManager::RangeManager()
{

}

void RangeManager::add(int start, int end)
{
    auto range = std::make_unique<Range>(start, end);
    if (!range->valid())
    {
        std::cout << "Invalid range provided (add): ";
        range->print();
        std::cout << std::endl;
        return;
    }

    std::vector<int> newRangeVec = range->toVec();
    std::vector<int> currentRanges = rangesToVec();

    // merge
    std::vector<int> newRanges;
    std::merge(newRangeVec.begin(), newRangeVec.end(),
               currentRanges.begin(), currentRanges.end(),
               std::back_inserter(newRanges));

    // remove duplicates
    auto last = std::unique(newRanges.begin(), newRanges.end());
    newRanges.erase(last, newRanges.end());

    std::cout << "Adding: " ;
    Util::print(newRangeVec);

    std::cout << "Old: ";
    Util::print((currentRanges));

    std::cout << "New range: ";
    Util::print(newRanges);

    ranges_.clear();

    auto first = newRanges.begin();
    auto n = newRanges.begin();

    n = std::adjacent_find(n, newRanges.end(), notSucc);
    std::cout << "First: " << *first << ", N: " << *(std::prev(n)) << std::endl;
    ranges_.push_back(new Range(*first, *(std::prev(n))));

    while (n < newRanges.end());
    {
        std::cout << "Looking" << std::endl;
        first = n;
        // n = std::adjacent_find(n, newRanges.end(), notSucc);
        //std::cout << "first: " << *first << ", N: " << *(n-1);
        std::cout << "Pushing";
        // ranges_.push_back(new Range(*first, *(n-1)));

    }

    std::cout << "Done add" << std::endl;

}

void RangeManager::del(int start, int end)
{
    auto range = std::make_unique<Range>(start, end);
    if (!range->valid())
    {
        std::cout << "Invalid range provided (del): ";
        range->print();
        std::cout << std::endl;
        return;
    }

    // nothing to delete from already empty range
    if (ranges_.size() == 0)
    {
        return;
    }


}

std::vector<Range *> RangeManager::get(int start, int end)
{
    auto range = std::make_unique<Range>(start, end);

    if (!range->valid())
    {
        std::cout << "Invalid range provided (get): ";
        range->print();
        std::cout << std::endl;
        return std::vector<Range*>();
    }

    return std::vector<Range*>();
}

void RangeManager::printRanges()
{
    std::cout << "Printing ranges: ";
    printRanges(ranges_);
}

void RangeManager::printRanges(std::vector<Range *> ranges)
{
    std::cout << "[";
    for (auto it = ranges.begin(); it < ranges.end(); it++)
    {
        (*it)->print();

        if (it != ranges.end()-1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

std::vector<int> RangeManager::rangesToVec()
{
    std::vector<int> result;
    for (Range * range : ranges_)
    {
        std::vector<int> rVec = range->toVec();
        result.insert(std::end(result), std::begin(rVec), std::end(rVec));
    }
    return result;
}
