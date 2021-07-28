#include "Intro.h"

#include <algorithm>

namespace ski {

uint32_t cycleLength(uint32_t n)
{
    if (n == 0)
    {
        return 0;
    }
    
    uint32_t cycles = 1;

    while (n != 1)
    {
        ++cycles;

        if (n % 2 == 1)
        {
            n = 3 * n + 1;
        }
        else
        {   
            n = n / 2;
        }
    }
    
    return cycles;
}

uint32_t maxCycleLength(uint32_t i, uint32_t j)
{
    uint32_t maxLength = 0;

    for (uint32_t k = i; k <= j; ++k)
    {
        maxLength = std::max(maxLength, cycleLength(k));
    }

    return maxLength;
}

} // namespace ski
