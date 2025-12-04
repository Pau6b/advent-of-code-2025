#include "Inputs/Day04.h"
#include <cstdint>
#include <array>
#include <iostream>

namespace Day04
{

bool IsPositionAccessible(std::vector<std::string>& i_map, int32_t i, int32_t j)
{
    //std::println("Checking {} - {}", i, j);
    static const std::array<std::array<int32_t, 2>, 8> variations = {{
        {{1,0}},
        {{-1,0}},
        {{0,1}},
        {{0,-1}},
        {{1,1}},
        {{-1,-1}},
        {{-1,1}},
        {{1,-1}}
    }};
    uint8_t paperRollsQuantity = 0;
    for (size_t idx = 0; idx < variations.size(); ++idx)
    {
        const int32_t newI = i + variations[idx][0];
        const int32_t newJ = j + variations[idx][1];
        if (!(0 <= newI && newI < i_map.size() && 0 <= newJ && newJ < i_map[newI].size()))
        {
            continue;
        }
        if (i_map[newI][newJ] == '@')
        {
            ++paperRollsQuantity;
            //std::println("paper roll found in {}, {}, variations", newI, newJ);
            if (paperRollsQuantity >= 4)
            {
                return false;
            }
        }
    }
    return true;
}

void Problem1()
{
    auto& inputData = input;
    uint64_t result = 0;
    for (size_t i = 0; i < inputData.size(); ++i)
    {
        for (size_t j = 0; j < inputData[i].size(); ++j)
        {
            if (inputData[i][j] == '@' && IsPositionAccessible(inputData, i, j))
            {
                ++result;
            }
        }
    }
    std::cout << result << "\n";
}

void Problem2()
{
    auto inputData = input;
    uint64_t result = 0;
    bool somethingChanged = true;
    while (somethingChanged)
    {
        somethingChanged = false;
        for (size_t i = 0; i < inputData.size(); ++i)
        {
            for (size_t j = 0; j < inputData[i].size(); ++j)
            {
                if (inputData[i][j] == '@' && IsPositionAccessible(inputData, i, j))
                {
                    ++result;
                    inputData[i][j] = '.';
                    somethingChanged = true;
                }
            }
        }
    }
    std::cout << result << "\n";
}

}