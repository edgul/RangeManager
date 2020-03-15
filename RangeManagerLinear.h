#ifndef RANGEMANAGERLINEAR_H
#define RANGEMANAGERLINEAR_H

#include "IRangeManager.h"

// all methods linear with respect to all values in the ranges set
class RangeManagerLinear : public IRangeManager
{
public:
    explicit RangeManagerLinear();

    void clear() override;
    std::vector<Range> get(int start, int end) const override;
    void add(int start, int end) override;
    void del(int start, int end) override;
    std::vector<int> toVec() const override;

private:
    std::vector<int> ranges_;
};

#endif // RANGEMANAGERLINEAR_H
