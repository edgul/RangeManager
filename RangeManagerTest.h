#ifndef RANGEMANAGERTEST_H
#define RANGEMANAGERTEST_H

#include "RangeManager.h"

class RangeManagerTest
{
public:
    RangeManagerTest();

    void invalidRanges();
    void validRanges();
    void clearRanges();
    void toVecRanges();
    void startEndRanges();

private:
    RangeManager rangeManager_;

    void passIfCondTrue(bool cond);
    void invalidRange(int start, int end);
    void validRange(int start, int end);
    void sameStartRange(Range &range1, Range &range2, bool expected);
    void sameEndRange(Range &r1, Range &r2, bool expected);

    int invalidRangeTestNum_;
    int validRangeTestNum_;
    int startEndRangeTestNum_;
    int clearRangeTestNum_;
};

#endif // RANGEMANAGERTEST_H
