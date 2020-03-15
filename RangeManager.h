#ifndef RANGEMANAGER_H
#define RANGEMANAGER_H

#include <vector>
#include "Range.h"

class RangeManager
{
public:
    explicit RangeManager();

    // all functions linear with respect to number of ranges (except toVec(), which touches all values)
    void clear();
    void add(int start, int end);
    void del(int start, int end);
    std::vector<Range> get(int start, int end) const;
    std::vector<int> toVec() const;

    // all functions linear with respect to all values in the ranges set
    void clearLinear();
    void addLinear(int start, int end);
    void delLinear(int start, int end);
    std::vector<Range*> getLinear(int start, int end) const;
    std::vector<int> toVecLinear() const;

private:
    std::vector<int> rangesLinear_;
    std::vector<Range> ranges_;

};

#endif // RANGEMANAGER_H
