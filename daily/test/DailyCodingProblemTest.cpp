#include <gtest/gtest.h>
#include "DailyCodingProblem.h"
#include <iostream>

TEST(DailyCodingProblemTest, FindClosestElements)
{
    using T = int;

    T k;
    T pivot;
    std::vector<T> numbers;
    std::vector<T> expected;
    std::vector<T> actual;
    
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
    actual   = findClosestElements(numbers, k, pivot);
    expected = {30, 35, 39, 42};

    EXPECT_EQ(actual, expected);
}