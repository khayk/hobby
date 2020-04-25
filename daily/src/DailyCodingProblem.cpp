#include "DailyCodingProblem.h"
#include <limits>
#include <cmath>
#include <algorithm>

std::vector<int> findClosestElements(const std::vector<int>& numbers, size_t k, int x)
{
    std::vector<int> result(k, std::numeric_limits<int>::max() / 2);
    size_t i = 0;

    for (auto n: numbers)
    {
        auto dist = std::abs(n - x);

        if (dist < std::abs(result[i] - x))
        {
            result[i++] = n;
            i = i % k;
        }
    }

    // now we need to perform cyclic shift, so that the smallest elements
    // positioned at the begining of the array
    std::rotate(result.begin(), result.begin() + i, result.end());

    return result;
}

