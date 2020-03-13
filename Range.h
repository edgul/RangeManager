#ifndef RANGE_H
#define RANGE_H

#include <vector>
#include <string>

class Range
{
public:
    explicit Range(int start, int end);
    ~Range();

    void clear();
    bool valid();
    std::vector<int> toVec();
    std::string toStr();

    int getStart();
    int getEnd();

private:
    int start_;
    int end_;
};

#endif // RANGE_H
