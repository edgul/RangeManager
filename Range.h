#ifndef RANGE_H
#define RANGE_H

#include <vector>

class Range
{
public:
    explicit Range(int start, int end);
    ~Range();

    void clear();
    void setStart(int start);
    void setEnd(int end);

    int start();
    int end();
    bool valid();
    void print();

    std::vector<int> toVec();

private:
    int start_;
    int end_;
};

#endif // RANGE_H
