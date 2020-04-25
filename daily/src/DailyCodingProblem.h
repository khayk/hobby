#ifndef __DAILY_CODING_PROBLEM_H__
#define __DAILY_CODING_PROBLEM_H__

#include <vector>
#include <type_traits>

/**
 * @brief Given a list of sorted numbers, and two integers k and x, 
 *        find k closest numbers to the pivot x.
 * 
 * @param numbers List of sorted numbers
 * @param k       Number of elements to find
 * @param x       The pivot
 */
//template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
std::vector<int> findClosestElements(const std::vector<int>& numbers, 
                                     size_t k, int x);

#endif // !__DAILY_CODING_PROBLEM_H__