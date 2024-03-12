#ifndef __DEITEL_TURTLE_GRAPHICS_H__
#define __DEITEL_TURTLE_GRAPHICS_H__

#include <vector>
#include <string>

/**
 * @brief Namespace for problems from Deitel book
 */
namespace deitel {

enum class Command
{
    PenUp       = 1,
    PenDown     = 2,
    TurnRight   = 3,
    TurnLeft    = 4,
    MoveForward = 5,
    Print       = 6,
    End         = 9
};

struct Pos
{
    int row {0};
    int col {0};

    Pos& operator+=(const Pos& pos)
    {
        row += pos.row;
        col += pos.col;

        return *this;
    }
};

static const Pos right {0, 1};
static const Pos down {1, 0};
static const Pos left {0, -1};
static const Pos up {-1, 0};

/**
 * @brief Simple implementation of exercise 7.23 (Turtle Graphics)
 */
class TurtleGraphics
{
    std::vector<std::string> floor_;
    bool penDown_ {false};
    int direction_ {0};
    Pos pos_;

public:
    /**
     * @brief Initial position is (0, 0) direction is `right`.
     * 
     * @param rows    Number of rows of the floor.
     * @param columns Number of columns of the floor.
     */
    TurtleGraphics(int rows, int columns);

    /**
     * @brief Run simulation.
     * 
     * @param input An input for the simulation.
     */
    void simulate(const std::vector<int>& input);

    /**
     * @brief Print the floor on the given destination.
     * 
     * @param dest Target of the result.
     */
    void print(std::string& dest);
};

} // namespace deitel

#endif // !__DEITEL_TURTLE_GRAPHICS_H__