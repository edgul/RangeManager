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
    bool valid() const;
    std::vector<int> toVec() const;
    std::string toStr() const;

    int getStart() const;
    int getEnd() const;

    bool intersects(Range& otherRange) const;
    bool operator==(const Range& rhs) const;

private:
    int start_;
    int end_;
};


#endif // RANGE_H
