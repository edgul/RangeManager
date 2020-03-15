#ifndef IRANGEMANAGER_H
#define IRANGEMANAGER_H

#include <vector>
#include "Range.h"

class IRangeManager
{
public:
    virtual void clear() = 0;
    virtual void add(int start, int end) = 0;
    virtual void del(int start, int end) = 0;
    virtual std::vector<Range> get(int start, int end) const = 0;
    virtual std::vector<int> toVec() const = 0;

};

#endif // IRANGEMANAGER_H
