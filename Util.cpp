#include "Util.h"

#include <iostream>
#include <iterator>

namespace Util {

void print(std::vector<int> v)
{
    std::cout << "[ ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "]" << std::endl;
}

}
