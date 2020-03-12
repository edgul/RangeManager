#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include "Range.h"

namespace Util {

void printVec(std::vector<int> v);
void printRanges(std::vector<Range*> ranges);

std::string vecToStr(std::vector<int> v);
std::string rangesToStr(std::vector<Range*> ranges);
}

#endif // UTIL_H
