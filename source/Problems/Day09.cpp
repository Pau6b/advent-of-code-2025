#include "Inputs/Day09.h"
#include <cstdlib>
#include <print>

namespace Day09
{

int64_t ComputeArea(const Point& i_first, const Point& i_second)
{
    return std::abs(i_first.x-i_second.x+1) * std::abs(i_first.y-i_second.y+1);
}

void Problem1()
{
    const auto& currentInput = input;

    int64_t maxArea = 0;
    for (size_t idx = 0; idx < currentInput.size(); ++idx)
    {
        for (size_t jdx = idx+1; jdx < currentInput.size(); ++jdx)
        {
            maxArea = std::max(maxArea, ComputeArea(currentInput[idx], currentInput[jdx]));
        }
    }
    std::println("result: {}", maxArea);
}

}