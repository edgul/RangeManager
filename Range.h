#ifndef RANGE_H
#define RANGE_H

#include <vector>

class Range
{
public:
    explicit Range(int start, int end);
    ~Range();

    void clear();
    bool valid();

    std::vector<int> toVec();
    std::string toStr();

private:
    int start_;
    int end_;
};

#endif // RANGE_H
