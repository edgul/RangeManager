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

    int size() const;
    int start() const;
    int end() const;

    bool contains(int value) const;
    bool intersects(const Range &otherRange) const;
    bool willMergeWith(const Range &other) const;
    void mergeWith(const Range&other);
    std::vector<Range> del(const Range& delRange);

    bool operator==(const Range& rhs) const;

private:
    int start_;
    int end_;

    Range shorter(const Range& r1, const Range&r2) const;
    Range longer(const Range& r1, const Range&r2) const;
};


#endif // RANGE_H
