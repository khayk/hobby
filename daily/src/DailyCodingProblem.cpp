#include "DailyCodingProblem.h"

#include <unordered_map>
#include <algorithm>
#include <limits>
#include <cmath>
#include <queue>
#include <array>

namespace dp {

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


std::vector<Point> findClosestPoints(const std::vector<Point>& points,
                                     const Point& origin,
                                     int k)
{
    struct PointInfo
    {
        size_t distance;
        size_t index;   // index of the element in the original `points` array
    };

    auto furthest = [](const PointInfo& lhs, const PointInfo& rhs)
    {
        return lhs.distance < rhs.distance;
    };

    // Prepare vector to prority queue, reserved beforehead
    std::vector<PointInfo> v;
    v.reserve(k);

    // Maintain a priority queue, where the top element is the fartest one
    std::priority_queue<PointInfo, std::vector<PointInfo>, decltype(furthest)>
        pq(furthest, std::move(v));

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
    size_t mismatchCount {0};
    std::array<size_t, 2> mismatches = {0};
    std::array<int, 26> firstFrequency {0};

    if (first.size() != second.size())
    {
        return false;
    }

    for (size_t i = 0; i < first.size(); ++i)
    {
        int relativeIndex = first[i] - 'a';

        if (relativeIndex < 0 || relativeIndex > 25)
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

    bool hasDuplicate = std::find_if(begin(firstFrequency), end(firstFrequency),
                        [](const int i) { return i > 1; }) != firstFrequency.end();

    bool hasSwap = (first[mismatches[0]] == second[mismatches[1]] && 
                    first[mismatches[1]] == second[mismatches[0]]);

    return  (mismatchCount == 0 && hasDuplicate) || (mismatchCount == 2 && hasSwap);
}

} // namespace dp