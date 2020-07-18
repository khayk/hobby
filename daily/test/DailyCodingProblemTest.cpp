#include <gtest/gtest.h>
#include "DailyCodingProblem.h"
#include <numeric>

using namespace dp;

TEST(DailyCodingProblemTest, FindClosestElements)
{
    size_t k {0};
    int pivot {0};
    std::vector<int> numbers;
    std::vector<int> expected;
    std::vector<int> actual;

    k        = 3;
    pivot    = 5;
    numbers  = {1, 3, 7, 8, 9};
    expected = {3, 7, 8};
    actual   = findClosestElements(numbers, k, pivot);
    EXPECT_EQ(actual, expected);

    k        = 4;
    pivot    = -1;
    numbers  = {1, 2, 3, 4, 5};
    expected = {1, 2, 3, 4};
    actual   = findClosestElements(numbers, k, pivot);
    EXPECT_EQ(actual, expected);

    k        = 4;
    pivot    = 3;
    numbers  = {1, 2, 3, 4, 5};
    expected = {1, 2, 3, 4};
    actual   = findClosestElements(numbers, k, pivot);
    EXPECT_EQ(actual, expected);

    k        = 4;
    pivot    = 35;
    numbers  = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
    expected = {30, 35, 39, 42};
    actual   = findClosestElements(numbers, k, pivot);
    EXPECT_EQ(actual, expected);
}


TEST(DailyCodingProblemTest, FindClosestPoints)
{
    size_t k {0};
    Point origin {0, 0};
    std::vector<Point> points;
    std::vector<Point> expected;
    std::vector<Point> actual;

    k        = 2;
    points   = {{0, 0}, {1, 2}, {-3, 4}, {3, 1}};
    expected = {{0, 0}, {1, 2}};
    actual   = findClosestPoints(points, origin, k);
    EXPECT_EQ(actual, expected);

    k        = 2;
    points   = {{3, 3}, {5, -1}, {-2, 4}};
    expected = {{3, 3}, {-2, 4}};
    actual   = findClosestPoints(points, origin, k);
    EXPECT_EQ(actual, expected);
}

TEST(DailyCodingProblemTest, IsBuddyStrings)
{
    std::string a;
    std::string b;

    a = "ab";
    b = "ba";
    EXPECT_EQ(isBuddyStrings(a, b), true);

    a = "ab";
    b = "ab";
    EXPECT_EQ(isBuddyStrings(a, b), false);

    a = "aa";
    b = "aa";
    EXPECT_EQ(isBuddyStrings(a, b), true);

    a = "aaaaaaabc";
    b = "aaaaaaacb";
    EXPECT_EQ(isBuddyStrings(a, b), true);

    a = "";
    b = "aa";
    EXPECT_EQ(isBuddyStrings(a, b), false);
}


TEST(DailyCodingProblemTest, IsNumber)
{
    EXPECT_EQ(isNumber("123"), true);   // Integer
    EXPECT_EQ(isNumber("12.3"), true);  // Floating point
    EXPECT_EQ(isNumber("-123"), true);  // Negative numbers
    EXPECT_EQ(isNumber("-.3"), true);   // Negative floating point
    EXPECT_EQ(isNumber("1.5e5"), true); // Scientific notation
    EXPECT_EQ(isNumber("5"), true);
    EXPECT_EQ(isNumber("0"), true);

    EXPECT_EQ(isNumber("12a"), false);
    EXPECT_EQ(isNumber("1 2"), false);
    EXPECT_EQ(isNumber("1e1.2"), false);
    EXPECT_EQ(isNumber("xabc"), false);
    EXPECT_EQ(isNumber("7.2a"), false);
    EXPECT_EQ(isNumber(""), false);
}

bool isBigEndian()
{
    union
    {
        uint32_t i;
        char c[4] {};
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

TEST(DailyCodingProblemTest, Utf8Validator)
{
    unsigned char buffer[8] = {0};
    size_t errorOffset {0};

    auto pack = [&](uint32_t value) {
        if (!isBigEndian())
        {
            memset(buffer, 0, sizeof(buffer));
            unsigned char* p = buffer;
            unsigned char* v =
                reinterpret_cast<unsigned char*>(&value) + sizeof(decltype(value)) - 1;

            while ((v > reinterpret_cast<unsigned char*>(&value)) && *v == 0)
            {
                --v;
            }

            while (v >= reinterpret_cast<unsigned char*>(&value))
            {
                *p++ = *v--;
            }
        }
        else
        {
            *reinterpret_cast<decltype(value)*>(buffer) = value;
        }
    };

    pack(0b00000000);
    EXPECT_EQ(utf8Validator(buffer, 1), true);

    pack(0b00000000'10000000);
    EXPECT_EQ(utf8Validator(buffer, 2, &errorOffset), false);
    EXPECT_EQ(errorOffset, 0U);

    pack(0b11000000'10000000);
    EXPECT_EQ(utf8Validator(buffer, 2), true);

    pack(0b11000010'10100010);
    EXPECT_EQ(utf8Validator(buffer, 2), true);

    pack(0b11100000'10100100'10111001); // ह character, 0xE0A4B9
    EXPECT_EQ(utf8Validator(buffer, 3), true);

    pack(0x0024); // $ character
    EXPECT_EQ(utf8Validator(buffer, 1), true);

    pack(0xC2A2); // ¢ character
    EXPECT_EQ(utf8Validator(buffer, 2), true);

    pack(0xE0A4B9); // ह character
    EXPECT_EQ(utf8Validator(buffer, 3), true);

    pack(0xE282AC); // € character
    EXPECT_EQ(utf8Validator(buffer, 3), true);

    pack(0xED959C); // 한 character
    EXPECT_EQ(utf8Validator(buffer, 3), true);

    pack(0xF0908D88); // 𐍈 character
    EXPECT_EQ(utf8Validator(buffer, 4), true);
}

TEST(DailyCodingProblemTest, RestoreIpAddresses)
{
    std::string digits;
    std::vector<std::string> expected;
    std::vector<std::string> actual;

    digits   = "1592551013";
    expected = {"159.255.10.13", "159.255.101.3"};
    actual   = restoreIpAddresses(digits);
    EXPECT_EQ(actual, expected);

    digits   = "25525511135";
    expected = {"255.255.11.135", "255.255.111.35"};
    actual   = restoreIpAddresses(digits);
    EXPECT_EQ(actual, expected);

    digits   = "110100100";
    expected = {"1.10.100.100", "11.0.100.100", "110.10.0.100", "110.100.10.0"};
    actual   = restoreIpAddresses(digits);
    EXPECT_EQ(actual, expected);

    digits   = "011010010";
    expected = {"0.110.100.10"};
    actual   = restoreIpAddresses(digits);
    EXPECT_EQ(actual, expected);

    digits   = "0000";
    expected = {"0.0.0.0"};
    actual   = restoreIpAddresses(digits);
    EXPECT_EQ(actual, expected);

    digits   = "010010";
    expected = {"0.10.0.10", "0.100.1.0"};
    actual   = restoreIpAddresses(digits);
    EXPECT_EQ(actual, expected);
}

TEST(DailyCodingProblemTest, MoveZeros)
{
    std::vector<int> numbers  = {0, 1, 0, 3, 12};
    std::vector<int> expected = {1, 3, 12, 0, 0};

    moveZeros(numbers);
    EXPECT_EQ(numbers, expected);

    numbers  = {0, 0, 0, 2, 0, 1, 3, 4, 0, 0};
    expected = {2, 1, 3, 4, 0, 0, 0, 0, 0, 0};

    moveZeros(numbers);
    EXPECT_EQ(numbers, expected);
}

TEST(DailyCodingProblemTest, RotateMatrix)
{
    std::vector<std::vector<int>> numbers  = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<int>> expected = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};

    rotateMatrix(numbers);
    EXPECT_EQ(numbers, expected);

    // clang-format off
    numbers  = {{ 1, 2, 3, 4}, { 5,  6, 7, 8}, { 9, 10, 11, 12}, {13, 14, 15, 16}};
    expected = {{13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11,  7,  3}, {16, 12,  8,  4}};
    // clang-format on

    rotateMatrix(numbers);
    EXPECT_EQ(numbers, expected);

    // clang-format off
    numbers  = {{ 1,  2,  3,  4,  5},
                { 6,  7,  8,  9, 10},
                {11, 12, 13, 14, 15},
                {16, 17, 18, 19, 20},
                {21, 22, 23, 24, 25}};

    expected = {{21, 16, 11,  6,  1},
                {22, 17, 12,  7,  2},
                {23, 18, 13,  8,  3},
                {24, 19, 14,  9,  4},
                {25, 20, 15, 10,  5}};
    // clang-format on

    rotateMatrix(numbers);
    EXPECT_EQ(numbers, expected);
}

TEST(DailyCodingProblemTest, UniqueWaysToClimbStairs)
{
    uint32_t stairs;
    uint64_t expected;
    uint64_t actual;

    stairs   = 4;
    actual   = uniqueWaysToClimbStairs(stairs);
    expected = 5;
    EXPECT_EQ(actual, expected);

    stairs   = 5;
    actual   = uniqueWaysToClimbStairs(stairs);
    expected = 8;
    EXPECT_EQ(actual, expected);

    stairs   = 10;
    actual   = uniqueWaysToClimbStairs(stairs);
    expected = 89;
    EXPECT_EQ(actual, expected);

    stairs   = 20;
    actual   = uniqueWaysToClimbStairs(stairs);
    expected = 10946;
    EXPECT_EQ(actual, expected);

    stairs   = 40;
    actual   = uniqueWaysToClimbStairs(stairs);
    expected = 165580141;
    EXPECT_EQ(actual, expected);
}

TEST(DailyCodingProblemTest, UniqueRooms)
{
    std::vector<std::pair<uint32_t, uint32_t>> intervals = {{30, 75}, {0, 50}, {60, 150}};
    uint32_t expected;
    uint32_t actual;

    expected = 2;
    actual   = uniqueRooms(intervals);
    EXPECT_EQ(actual, expected);
}

TEST(DailyCodingProblemTest, FindDuplicates)
{
    std::vector<uint32_t> numbers;
    std::vector<uint32_t> expected;
    std::vector<uint32_t> actual;

    numbers  = {4, 3, 2, 7, 8, 2, 3, 1};
    expected = {2, 3};
    actual   = findDuplicates(numbers);

    EXPECT_EQ(actual, expected);

    numbers  = {1, 2, 1};
    expected = {1};
    actual   = findDuplicates(numbers);

    EXPECT_EQ(actual, expected);

    numbers  = {7, 8, 3, 4, 7, 6, 6, 8};
    expected = {6, 7, 8};
    actual   = findDuplicates(numbers);

    EXPECT_EQ(actual, expected);
}

TEST(DailyCodingProblemTest, FindPairWithGivenSum)
{
    std::vector<int> numbers {10, 15, 3, 7};

    EXPECT_EQ(findPairWithGivenSum(numbers, 17), true);
    EXPECT_EQ(findPairWithGivenSum(numbers, 26), false);
}

TEST(DailyCodingProblemTest, ContiguousSumToK)
{
    auto rangeSum = [](const std::vector<int>& numbers,
                       const std::pair<int, int>& range) {
        return std::accumulate(numbers.begin() + range.first,
                               numbers.begin() + range.second + 1,
                               0);
    };

    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::pair<int, int> out;

    EXPECT_EQ(contiguousSumToK(numbers, 9, out), true);
    EXPECT_EQ(rangeSum(numbers, out), 9);

    EXPECT_EQ(contiguousSumToK(numbers, 10, out), true);
    EXPECT_EQ(rangeSum(numbers, out), 10);

    EXPECT_EQ(contiguousSumToK(numbers, 6, out), true);
    EXPECT_EQ(rangeSum(numbers, out), 6);

    EXPECT_EQ(contiguousSumToK(numbers, 15, out), true);
    EXPECT_EQ(rangeSum(numbers, out), 15);

    EXPECT_EQ(contiguousSumToK(numbers, 16, out), false);

    numbers = {1, 1, 7};
    EXPECT_EQ(contiguousSumToK(numbers, 7, out), true);
    EXPECT_EQ(rangeSum(numbers, out), 7);

    EXPECT_EQ(contiguousSumToK(numbers, 8, out), true);
    EXPECT_EQ(rangeSum(numbers, out), 8);

    EXPECT_EQ(contiguousSumToK(numbers, 9, out), true);
    EXPECT_EQ(rangeSum(numbers, out), 9);

    numbers = {9, 4, 20, 3, 10, 5};
    EXPECT_EQ(contiguousSumToK(numbers, 33, out), true);
    EXPECT_EQ(rangeSum(numbers, out), 33);

    // @todo:hayk - doesn't work for negative numbers, correct
    numbers = {10, 2, -2, -20, 10};
    EXPECT_EQ(contiguousSumToK(numbers, -10, out), true);
    EXPECT_EQ(rangeSum(numbers, out), -10);
}