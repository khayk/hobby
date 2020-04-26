#ifndef __DAILY_CODING_PROBLEM_H__
#define __DAILY_CODING_PROBLEM_H__

#include <cstdint>
#include <vector>
#include <type_traits>

using Point = std::tuple<int, int>;

/**
 * @brief Given a list of sorted numbers, and two integers k and x,
 *        find k closest numbers to the pivot x.
 *
 * @param numbers List of sorted numbers
 * @param k       Number of elements to find
 * @param x       The pivot
 *
 * @return vector k closes numbers
 */
std::vector<int> findClosestElements(const std::vector<int>& numbers,
                                     size_t k, int x);

/**
 * @brief Given a list of points as a tuple (x, y) and an integer k,
 *        find the k closest points to the origin (0, 0).
 *
 * @param points List of points
 * @param origin The origin point to measure distance from
 * @param k      Number of elements to find
 *
 * @return vector of k closes points
 */
std::vector<Point> findClosestPoints(const std::vector<Point>& points,
                                     const Point& origin,
                                     int k);


#endif // !__DAILY_CODING_PROBLEM_H__