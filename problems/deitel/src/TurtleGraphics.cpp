#include "TurtleGraphics.h"
#include <stdexcept>
#include <iostream>

namespace deitel {
namespace details {
Command readCommand(const std::vector<int>& input, size_t pos)
{
    if (pos < input.size())
    {
        return static_cast<Command>(input[pos]);
    }

    throw std::out_of_range("Invalid position for command in the input array.");
}

int readArgument(const std::vector<int>& input, size_t pos)
{
    if (pos < input.size())
    {
        return input[pos];
    }

    throw std::out_of_range("Invalid position for argument in the input array.");
}

} // namespace details

TurtleGraphics::TurtleGraphics(int rows, int columns)
    : floor_(rows, std::string(columns, ' '))
{
}

void TurtleGraphics::simulate(const std::vector<int>& input)
{
    std::vector<Pos> dirs = {right, down, left, up};

    std::string output;
    int steps = 0;

    for (auto i = 0u; i < input.size(); ++i)
    {
        auto command = details::readCommand(input, i);

        switch (command)
        {
            case Command::PenUp:
                penDown_ = false;
                break;

            case Command::PenDown:
                penDown_ = true;
                break;

            case Command::TurnRight:
                ++direction_;
                break;

            case Command::TurnLeft:
                --direction_;
                break;

            case Command::MoveForward:
                steps = details::readArgument(input, ++i);
                while (steps-- > 0)
                {
                    floor_[pos_.row][pos_.col] = penDown_ ? '*' : ' ';
                    pos_ += dirs[direction_];
                }
                break;

            case Command::Print:
                print(output);
                std::cout << output << std::endl;
                break;

            case Command::End:
                return;

            default:
                throw std::runtime_error("Invalid command");
        }

        direction_ %= 4;
    }
}

void TurtleGraphics::print(std::string& dest)
{
    dest.reserve((floor_.size() + 1) * floor_[0].size());
    dest.clear();

    for (const auto& row : floor_)
    {
        dest.append(row);
        dest.push_back('\n');
    }
}

} // namespace deitel