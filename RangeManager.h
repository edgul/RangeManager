#ifndef RANGEMANAGER_H
#define RANGEMANAGER_H

#include <vector>
#include "Range.h"

class RangeManager
{
public:
    explicit RangeManager();

    void add(int start, int end);
    void del(int start, int end);
    std::vector<Range*> get(int start, int end);

    void printRanges();
    static void printRanges(std::vector<Range*> ranges);

private:
    std::vector<Range*> ranges_;

    std::vector<int> rangesToVec();

};

#endif // RANGEMANAGER_H
