#include <gtest/gtest.h>
#include "DailyCodingProblem.h"
#include <iostream>

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