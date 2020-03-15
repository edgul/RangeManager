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

    void setStart(int start);
    void setEnd(int end);
    int getStart() const;
    int getEnd() const;

    bool contains(int value) const;
    bool lower(int value) const;
    bool higher(int value) const;

    bool hasHigher(const Range& other) const;
    bool hasLower(const Range& other) const;
    bool intersects(const Range &otherRange) const;
    bool operator==(const Range& rhs) const;

    int size() const;

    std::vector<Range> add(const Range& other) const;

    static Range shorter(const Range& r1, const Range&r2);
    static Range longer(const Range& r1, const Range&r2);


private:
    int start_;
    int end_;
};


#endif // RANGE_H
