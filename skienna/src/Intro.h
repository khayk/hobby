#pragma once

#include <cstdint>

namespace ski {

/**
 * @brief  The 3n + 1 problem, given an input n, it is possible to determine the number of
 * numbers printed before and including the 1 is printed
 *
 * @param n
 * @return
 */
uint32_t cycleLength(uint32_t n);

/**
 * @brief  The input will consist of a series of pairs of integers i and j, one pair of
 * integers per line. All integers will be less than 10,000 and greater than 0.
 *
 * @param i
 * @param j
 * @return
 */
uint32_t maxCycleLength(uint32_t i, uint32_t j);

} // namespace ski
