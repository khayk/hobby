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

/**
 * @brief Given a square 2D matrix (n x n), rotate the matrix by 90 degrees clockwise.
 *
 * @param matrix An input matrix.
 */
void rotateMatrix(std::vector<std::vector<int>>& matrix);

/**
 * @brief Given a positive integer N which represents the number of steps in a staircase. You can either climb 1 or 2 steps at a time.
 *
 * @param stairs Represents the number of steps in a staircase
 *
 * @return The number of unique ways to climb the stairs.
*/
uint64_t uniqueWaysToClimbStairs(uint32_t stairs);

/**
 * @brief You are given an array of tuples (start, end) representing time intervals
 *        for lectures. The intervals may be overlapping. Return the number of
 *        rooms that are required.
 *
 * @param intervals An array of intervals
 *
 * @return uint32_t Number of rooms required
 */
uint32_t uniqueRooms(std::vector<std::pair<uint32_t, uint32_t>>& intervals);

/**
 * @brief Given an array of size n, and all values in the array are in the range 1 to n,
 *        find all the duplicates.
 *
 * @param numbers The array of numbers in the range 1 to n
 *
 * @return The array of duplicates
 */
std::vector<uint32_t> findDuplicates(const std::vector<uint32_t>& numbers);

/**
 * @brief  Given a list of numbers and a number k, return whether any two
 *         numbers from the list add up to k. (asked by Google)
 *
 * @example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.
 *
 * Bonus: Can you do this in one pass?
 *
 * @param numbers  Array of integer numbers
 * @param k        Given sum of searched 2 pairs
 *
 * @return true  if such a pair exists, false otherwise
 */
bool findPairWithGivenSum(const std::vector<int>& numbers, int k);

/**
 * @brief   Given a list of integers and a number k, return which contiguous
 *          elements of the list sum to k.
 *
 *          For example, if the list is [1, 2, 3, 4, 5] and K is 9, then it
 *          should return [2, 3, 4].
 *
 * @param numbers  List of integers
 * @param k        Value of the sum
 * @return bool    true if such sequence is found, otherwise false.
 */
bool contiguousSumToK(const std::vector<int>& numbers, int k, std::pair<int, int>& out);

/**
 * @brief Given a list of numbers, where every number shows up twice except
 *        for one number, find that one number.
 *
 * @param numbers  List of integers
 * @return int     Return the non duplicate number
 */
int findUniqueNumber(const std::vector<int>& numbers);

} // namespace dp

#endif // !__DAILY_CODING_PROBLEM_H__