#include <gtest/gtest.h>
#include "TurtleGraphics.h"

using namespace deitel;

TEST(TurtleGraphicsTest, DrawSquare)
{
    const size_t width  = 20;
    const size_t height = 20;

    TurtleGraphics graphics(width, height);

    std::vector<int> input = {5, 15, 3, 5, 3, 2, 5, 12, 3, 5, 12, 3, 5, 12, 3, 5, 12, 1, 9};

    graphics.simulate(input);

    std::string output;
    graphics.print(output);

    std::string expected = "                    \n"
                           "                    \n"
                           "                    \n"
                           "   *************    \n"
                           "   *           *    \n"
                           "   *           *    \n"
                           "   *           *    \n"
                           "   *           *    \n"
                           "   *           *    \n"
                           "   *           *    \n"
                           "   *           *    \n"
                           "   *           *    \n"
                           "   *           *    \n"
                           "   *           *    \n"
                           "   *           *    \n"
                           "   *************    \n"
                           "                    \n"
                           "                    \n"
                           "                    \n"
                           "                    \n";

    EXPECT_EQ(expected, output);
}

TEST(TurtleGraphicsTest, DrawLine)
{
    const size_t width  = 5;
    const size_t height = 5;

    TurtleGraphics graphics(width, height);

    std::vector<int> input = {
        2, 5, 1, 3, 1, 5, 1, 4, 
        2, 5, 1, 3, 1, 5, 1, 4, 
        2, 5, 1, 3, 1, 5, 1, 4,
        2, 5, 1, 3, 1, 5, 1, 4, 
        2, 5, 1, 3, 1, 5, 1, 4, 
        9
    };

    graphics.simulate(input);

    std::string output;
    graphics.print(output);

    std::string expected = "*    \n"
                           " *   \n"
                           "  *  \n"
                           "   * \n"
                           "    *\n";

    EXPECT_EQ(expected, output);
}

TEST(TurtleGraphicsTest, DrawStais)
{
    const size_t width  = 5;
    const size_t height = 5;

    TurtleGraphics graphics(width, height);

    std::vector<int> input = {2, 
        5, 1, 3, 5, 1, 4, 
        5, 1, 3, 5, 1, 4, 
        5, 1, 3, 5, 1, 4,
        5, 1, 3, 5, 1, 4,
        5, 1, 3, 5, 1, 4,
        9};

    graphics.simulate(input);

    std::string output;
    graphics.print(output);

    std::string expected = "**   \n"
                           " **  \n"
                           "  ** \n"
                           "   **\n"
                           "    *\n";

    EXPECT_EQ(expected, output);
}