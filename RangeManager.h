#ifndef RANGEMANAGER_H
#define RANGEMANAGER_H

#include <vector>
#include "Range.h"

class RangeManager
{
public:
    explicit RangeManager();

    void clear();
    void add(int start, int end);
    void del(int start, int end);
    std::vector<Range*> get(int start, int end) const;
    std::vector<int> toVec() const;

private:
    std::vector<int> ranges_;

};

#endif // RANGEMANAGER_H
