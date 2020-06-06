#ifndef __DAILY_CODING_PROBLEM_H__
#define __DAILY_CODING_PROBLEM_H__

#include <cstdint>
#include <vector>
#include <type_traits>
#include <string>

/**
 * @brief Namespace for Daily Problem
 */
namespace dp {

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
std::vector<int> findClosestElements(const std::vector<int>& numbers, size_t k, int x);

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
                                     size_t k);

/**
 * @brief Given two strings A and B of lowercase letters, return true if and
 *        only if we can swap two letters in A so that the result equals B.
 *
 * @param first  First string
 * @param second Second string
 *
 * @return Boolean answer to the original question
 */
bool isBuddyStrings(const std::string& first, const std::string& second);

/**
 * @brief  Given a string that may represent a number, determine if it is a number
 *
 * @param str  Input string
 *
 * @return true if the string represents a number, false otherwise
 */
bool isNumber(const std::string& str);


/**
 * @brief Given a chunk of memory, return whether or not the it represnets a
 *        valid UTF-8 encoding.
 *
 * @param data The memory to check
 * @param size The size of the memory
 * @param errorOffset If provided by the user should used to return offset of the first
 *                    invalid byte that is supposed to be the part of UTF-8 encoding
 * @return true if the given memory represent a characters written with UTF-8 encoding
 */
bool utf8Validator(const unsigned char* data, size_t size, size_t* errorOffset = 0);
bool utf8Validator(const std::string& data, size_t* errorOffset = 0);


/**
 * @brief Given a string containing only digits, restore it by returning all
 *        possible valid IP address combinations.
 *
 * @note A valid IP address consists of exactly four integers (each integer
 *       is between 0 and 255) separated by single points.
 *
 * @param digits string of digits
 *
 * @return vector of valid ip address
 */
std::vector<std::string> restoreIpAddresses(const std::string& digits);

/**
 * @brief Move all 0's to the end of the array while maintaining the
 *        relative order of the non-zero elements.
 *
 * @param numbers The array of integers
 */
void moveZeros(std::vector<int>& numbers);

} // namespace dp

#endif // !__DAILY_CODING_PROBLEM_H__