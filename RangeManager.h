#ifndef RANGEMANAGER_H
#define RANGEMANAGER_H

#include "IRangeManager.h"

// all methods linear with respect to number of ranges (except toVec(), which touches all values within each range)
class RangeManager : public IRangeManager
{
public:
    explicit RangeManager();

    void clear() override;
    std::vector<Range> get(int start, int end) const override;
    void add(int start, int end) override;
    void del(int start, int end) override;
    std::vector<int> toVec() const override;

private:
    std::vector<Range> ranges_;
};

#endif // RANGEMANAGER_H
