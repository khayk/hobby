#include <gtest/gtest.h>
#include "DailyCodingProblem.h"

using namespace dp;

TEST(DailyCodingProblemTest, FindClosestElements)
{
    size_t k;
    int pivot;
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
    size_t k;
    Point origin {0, 0};
    std::vector<Point> points;
    std::vector<Point> expected;
    std::vector<Point> actual;

    k = 2;
    points   = {{0, 0}, {1, 2}, {-3, 4}, {3, 1}};
    expected = {{0, 0}, {1, 2}};
    actual   = findClosestPoints(points, origin, k);
    EXPECT_EQ(actual, expected);

    k = 2;
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
    EXPECT_EQ(isNumber("123"),   true);   // Integer
    EXPECT_EQ(isNumber("12.3"),  true);   // Floating point
    EXPECT_EQ(isNumber("-123"),  true);   // Negative numbers
    EXPECT_EQ(isNumber("-.3"),   true);   // Negative floating point
    EXPECT_EQ(isNumber("1.5e5"), true);   // Scientific notation
    EXPECT_EQ(isNumber("5"),     true);
    EXPECT_EQ(isNumber("0"),     true);

    EXPECT_EQ(isNumber("12a"),   false);
    EXPECT_EQ(isNumber("1 2"),   false);
    EXPECT_EQ(isNumber("1e1.2"), false);
    EXPECT_EQ(isNumber("xabc"),  false);
    EXPECT_EQ(isNumber("7.2a"),  false);
    EXPECT_EQ(isNumber(""),      false);
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
    size_t errorOffset;

    auto pack = [&](uint32_t value)
    {
        if (!isBigEndian())
        {
            memset(buffer, 0, sizeof(buffer));
            unsigned char* p = buffer;
            unsigned char* v = (unsigned char*) &value + sizeof(decltype(value)) - 1;

            while ((v > (unsigned char*) &value) && *v == 0)
                --v;

            while (v >= (unsigned char*) &value)
                *p++ = *v--;
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
    EXPECT_EQ(errorOffset, 0u);

    pack(0b11000000'10000000);
    EXPECT_EQ(utf8Validator(buffer, 2), true);

    pack(0b11000010'10100010);
    EXPECT_EQ(utf8Validator(buffer, 2), true);

    pack(0b11100000'10100100'10111001); // ह character, 0xE0A4B9
    EXPECT_EQ(utf8Validator(buffer, 3), true);

    pack(0x0024);       // $ character
    EXPECT_EQ(utf8Validator(buffer, 1), true);

    pack(0xC2A2);       // ¢ character
    EXPECT_EQ(utf8Validator(buffer, 2), true);

    pack(0xE0A4B9);     // ह character
    EXPECT_EQ(utf8Validator(buffer, 3), true);

    pack(0xE282AC);     // € character
    EXPECT_EQ(utf8Validator(buffer, 3), true);

    pack(0xED959C);     // 한 character
    EXPECT_EQ(utf8Validator(buffer, 3), true);

    pack(0xF0908D88);   // 𐍈 character
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

    digits = "110100100";
    expected = {"1.10.100.100", "11.0.100.100", "110.10.0.100", "110.100.10.0"};
    actual = restoreIpAddresses(digits);
    EXPECT_EQ(actual, expected);

    digits = "011010010";
    expected = {"0.110.100.10"};
    actual = restoreIpAddresses(digits);
    EXPECT_EQ(actual, expected);

    digits = "0000";
    expected = {"0.0.0.0"};
    actual = restoreIpAddresses(digits);
    EXPECT_EQ(actual, expected);

    digits = "010010";
    expected = {"0.10.0.10", "0.100.1.0"};
    actual = restoreIpAddresses(digits);
    EXPECT_EQ(actual, expected);
}

TEST(DailyCodingProblemTest, MoveZeros)
{
    std::vector<int> numbers = {0, 1, 0, 3, 12};
    std::vector<int> expected = {1, 3, 12, 0, 0};

    moveZeros(numbers);
    EXPECT_EQ(numbers, expected);

    numbers  = {0, 0, 0, 2, 0, 1, 3, 4, 0, 0};
    expected = {2, 1, 3, 4, 0, 0, 0, 0, 0, 0};

    moveZeros(numbers);
    EXPECT_EQ(numbers, expected);
}