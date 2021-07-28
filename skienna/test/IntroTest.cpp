#include <gtest/gtest.h>
#include "Intro.h"

using namespace ski;

TEST(IntroTest, CycleLength)
{
    EXPECT_EQ(cycleLength(22), 16u);

    uint64_t totalLength = 0;
    for (uint32_t i = 1; i <= 10000; ++i)
    {
        totalLength += cycleLength(i);
    }

    EXPECT_EQ(totalLength, 859666u);
}


TEST(IntroTest, MaxCycleLength)
{
    EXPECT_EQ(maxCycleLength(1, 10), 20u);
    EXPECT_EQ(maxCycleLength(100, 200), 125u);
    EXPECT_EQ(maxCycleLength(201, 210), 89u);
    EXPECT_EQ(maxCycleLength(900, 1000), 174u);
}
