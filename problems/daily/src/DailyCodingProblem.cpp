#include "DailyCodingProblem.h"

#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <limits>
#include <cmath>
#include <queue>
#include <array>
#include <iterator>
#include <system_error>

//#define INTERACTIVE

#ifdef INTERACTIVE
    #include <iostream>

std::ostream& stream()
{
    return std::cout;
}
#else
class NullStream
{
};

template <typename T>
NullStream& operator<<(NullStream& ns, const T& /*unused*/)
{
    return ns;
}

NullStream& stream()
{
    static NullStream ns;
    return ns;
}
#endif

namespace dp {

std::vector<int> findClosestElements(const std::vector<int>& numbers, size_t k, int x)
{
    std::vector<int> result(k, std::numeric_limits<int>::max() / 2);
    size_t i = 0;

    for (auto n : numbers)
    {
        auto dist = std::abs(n - x);

        if (dist < std::abs(result[i] - x))
        {
            result[i++] = n;
            i           = i % k;
        }
    }

    // now we need to perform cyclic shift, so that the smallest elements
    // positioned at the begining of the array
    std::rotate(result.begin(), result.begin() + i, result.end());

    return result;
}


std::vector<Point> findClosestPoints(const std::vector<Point>& points,
                                     const Point& origin,
                                     size_t k)
{
    struct PointInfo
    {
        size_t distance;
        size_t index; // index of the element in the original `points` array
    };

    auto furthest = [](const PointInfo& lhs, const PointInfo& rhs) {
        return lhs.distance < rhs.distance;
    };

    // Prepare vector to priority queue, reserved beforehead
    std::vector<PointInfo> v;
    v.reserve(k);

    // Maintain a priority queue, where the top element is the fartest one
    std::priority_queue<PointInfo, std::vector<PointInfo>, decltype(furthest)> pq(
        furthest,
        std::move(v));

    for (size_t i = 0; i < points.size(); ++i)
    {
        const auto& p   = points[i];
        size_t dx       = std::abs(std::get<0>(p) - std::get<0>(origin));
        size_t dy       = std::abs(std::get<1>(p) - std::get<1>(origin));
        size_t distance = dx * dx + dy * dy;

        if (pq.size() >= k && pq.top().distance > distance)
        {
            pq.pop();
        }

        if (pq.size() < k)
        {
            pq.push(PointInfo {distance, i});
        }
    }

    std::vector<Point> result(pq.size());
    auto rit = result.rbegin();

    while (!pq.empty())
    {
        *rit++ = points[pq.top().index];
        pq.pop();
    }

    return result;
}


bool isBuddyStrings(const std::string& first, const std::string& second)
{
    const int alphabetSize = 26;
    size_t mismatchCount {0};
    std::array<size_t, 2> mismatches {0};
    std::array<int, alphabetSize> firstFrequency {0};

    if (first.size() != second.size())
    {
        return false;
    }

    for (size_t i = 0; i < first.size(); ++i)
    {
        int relativeIndex = first[i] - 'a';

        if (relativeIndex < 0 || relativeIndex > alphabetSize - 1)
        {
            return false;
        }

        ++firstFrequency[relativeIndex];

        if (first[i] != second[i])
        {
            mismatches[mismatchCount++] = i;

            if (mismatchCount > 2)
            {
                return false;
            }
        }
    }

    bool hasDuplicate =
        std::find_if(begin(firstFrequency), end(firstFrequency), [](const int i) {
            return i > 1;
        }) != firstFrequency.end();

    bool hasSwap = (first[mismatches[0]] == second[mismatches[1]] &&
                    first[mismatches[1]] == second[mismatches[0]]);

    return (mismatchCount == 0 && hasDuplicate) || (mismatchCount == 2 && hasSwap);
}


bool isNumber(const std::string& str)
{
    bool signProcessed {false};
    bool decimalPointProcessed {false};
    bool scientificSymbolProcessed {false};
    bool digitDiscovered {false};

    for (auto ch : str)
    {
        if (isdigit(ch))
        {
            // no sign is allowed after the digit
            signProcessed   = true;
            digitDiscovered = true;
        }
        else if (ch == '-' || ch == '+')
        {
            if (signProcessed || decimalPointProcessed)
            {
                return false;
            }
            signProcessed = true;
        }
        else if (ch == '.')
        {
            if (decimalPointProcessed || scientificSymbolProcessed)
            {
                return false;
            }
            decimalPointProcessed = true;
        }
        else if (ch == 'e')
        {
            if (scientificSymbolProcessed || !digitDiscovered)
            {
                return false;
            }
            scientificSymbolProcessed = true;
        }
        else
        {
            return false;
        }
    }

    return !str.empty() && isdigit(str.back());
}


bool utf8Validator(const unsigned char* data, size_t size, size_t* errorOffset)
{
    // 1 byte:   0xxxxxxx
    // 2 bytes:  110xxxxx 10xxxxxx
    // 3 bytes : 1110xxxx 10xxxxxx 10xxxxxx
    // 4 bytes : 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

    const unsigned char masks[] = {
        0x80, // 10000000
        0xE0, // 11100000
        0xF0, // 11110000
        0xF8  // 11111000
    };

    const unsigned char byteEqual[] = {
        0x0,  // 00000000
        0xC0, // 11000000
        0xE0, // 11100000
        0xF0  // 11110000
    };

    // reset any offset before starting validation
    if (errorOffset != nullptr)
    {
        *errorOffset = 0;
    }

    const size_t c         = sizeof(masks) / sizeof(masks[0]);
    const unsigned char* p = data;
    const unsigned char* e = data + size;

    while (p < e)
    {
        // most common case
        if ((*p & masks[0]) == byteEqual[0])
        {
            ++p;
        }
        else
        {
            size_t i = 0;
            for (i = 1; i < c; ++i)
            {
                if ((*p & masks[i]) == byteEqual[i])
                {
                    ++p;

                    // expecting pattern 10xxxxxx i times
                    for (size_t j = 0; j < i; ++j)
                    {
                        if (masks[0] != (*p & byteEqual[1]))
                        {
                            if (errorOffset != nullptr)
                            {
                                *errorOffset = p - data;
                            }

                            return false;
                        }

                        ++p;
                    }

                    break;
                }
            }

            if (i == c)
            {
                if (errorOffset != nullptr)
                {
                    *errorOffset = p - data;
                }

                return false;
            }
        }
    }

    return true;
}


bool utf8Validator(const std::string& data, size_t* errorOffset)
{
    return utf8Validator(reinterpret_cast<const unsigned char*>(data.data()),
                         data.size(),
                         errorOffset);
}


bool isValidBlock(const std::string& digits, size_t offset, const size_t length)
{
    if (offset >= digits.size())
    {
        return false;
    }

    // corner case handling
    if (digits[offset] == '0')
    {
        return length == 1;
    }

    size_t n = 0;

    for (size_t i = offset; i < digits.size() && i < offset + length; ++i)
    {
        n = 10 * n + digits[i] - '0';
    }

    return (n > 0 && n < 256);
}


void extractGroups(const std::string& digits,
                   size_t offset,
                   size_t groups,
                   std::vector<std::string>& result)
{
    if (groups == 1)
    {
        if (isValidBlock(digits, offset, digits.size() - offset))
        {
            result.push_back(digits.substr(offset));
        }

        return;
    }

    std::string candidate;

    for (int i = 1; i <= 3; ++i)
    {
        std::vector<std::string> local;

        if (isValidBlock(digits, offset, i))
        {
            candidate = digits.substr(offset, i);
            extractGroups(digits, offset + i, groups - 1, local);

            for (const auto& l : local)
            {
                result.push_back(std::string(candidate).append(1, '.').append(l));
            }
        }
    }
}


std::vector<std::string> restoreIpAddresses(const std::string& digits)
{
    std::vector<std::string> addresses;
    extractGroups(digits, 0, 4, addresses);

    return addresses;
}


void moveZeros(std::vector<int>& numbers)
{
    size_t writePos = 0;

    for (size_t i = 0; i < numbers.size(); ++i)
    {
        if (numbers[i] != 0)
        {
            numbers[writePos] = numbers[i];
            writePos++;
        }
    }

    while (writePos < numbers.size())
    {
        numbers[writePos++] = 0;
    }
}


void rotateMatrix(std::vector<std::vector<int>>& matrix)
{
    size_t n = matrix.size();

    for (size_t i = 0; i < (n + 1) / 2; ++i)
    {
        for (size_t j = i; j < n - i - 1; ++j)
        {
            auto p = i;
            auto q = j;
            auto t = matrix[p][q];

            for (int k = 0; k < 3; ++k)
            {
                matrix[p][q] = matrix[n - q - 1][p];
                auto l       = p;
                p            = n - q - 1;
                q            = l;
            }

            matrix[p][q] = t;
        }
    }
}


uint64_t uniqueWaysToClimbStairsHelper(uint32_t stairs, std::vector<uint64_t>& dp)
{
    if (stairs <= 2)
    {
        return stairs;
    }

    if (dp[stairs] != 0)
    {
        return dp[stairs];
    }

    dp[stairs - 1] = uniqueWaysToClimbStairsHelper(stairs - 1, dp);
    dp[stairs - 2] = uniqueWaysToClimbStairsHelper(stairs - 2, dp);

    return dp[stairs - 1] + dp[stairs - 2];
}


uint64_t uniqueWaysToClimbStairs(uint32_t stairs)
{
    std::vector<uint64_t> dp(static_cast<uint64_t>(stairs) + 1, 0);

    return uniqueWaysToClimbStairsHelper(stairs, dp);
}


uint32_t uniqueRooms(std::vector<std::pair<uint32_t, uint32_t>>& intervals)
{
    std::sort(begin(intervals), end(intervals), [](const auto& l, const auto& r) {
        if (l.first == r.first)
        {
            return l.second <= r.second;
        }

        return l.first < r.first;
    });

    std::priority_queue<uint32_t, std::vector<uint32_t>, std::greater<>> q;
    uint32_t count = 0;

    for (const auto& i : intervals)
    {
        const auto s = i.first;
        const auto e = i.second;

        if (q.empty())
        {
            ++count;
        }
        else
        {
            if (s >= q.top())
            {
                q.pop();
            }
            else
            {
                ++count;
            }
        }

        q.push(e);
    }

    return count;
}


std::vector<uint32_t> findDuplicates(const std::vector<uint32_t>& numbers)
{
    auto n = static_cast<uint32_t>(numbers.size());
    std::vector<uint32_t> duplicates(n, 0);

    for (const auto& v : numbers)
    {
        if (v < 1 && v > n)
        {
            throw std::system_error(std::make_error_code(std::errc::invalid_argument));
        }

        duplicates[v - 1] += n;
    }

    for (uint32_t i = 0; i < n; ++i)
    {
        if (duplicates[i] > n)
        {
            duplicates[i] = i + 1;
        }
        else
        {
            duplicates[i] = 0;
        }
    }

    auto it = std::remove_if(std::begin(duplicates),
                             std::end(duplicates),
                             [](const uint32_t& v) {
                                 return v == 0;
                             });
    duplicates.erase(it, std::end(duplicates));

    return duplicates;
}


bool findPairWithGivenSum(const std::vector<int>& numbers, int k)
{
    std::unordered_set<int> pairs;

    for (auto i : numbers)
    {
        if (pairs.find(k - i) != pairs.end())
        {
            stream() << "pair with given sum " << k << " is (" << i << ", " << k - i
                     << ")\n";
            return true;
        }

        pairs.insert(i);
    }

    return false;
}


bool contiguousSumToK(const std::vector<int>& numbers,
                      const int k,
                      std::pair<int, int>& out)
{
    std::unordered_map<int, size_t> sums;

    int sum = 0;
    for (auto i = 0; i < static_cast<int>(numbers.size()); ++i)
    {
        sums.insert({sum, i});
        sum += numbers[i];

        auto it = sums.find(sum - k);

        if (it != sums.end())
        {
            out.first  = static_cast<int>(it->second);
            out.second = i;
            return true;
        }
    }

    return false;
}


int findUniqueNumber(const std::vector<int>& numbers)
{
    int unique = 0;

    for (const auto& i: numbers)
    {
        unique ^= i;
    }

    return unique;
}

} // namespace dp