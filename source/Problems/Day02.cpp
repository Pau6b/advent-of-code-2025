#include <numeric>
#include <print>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include "Inputs/Day02.h"

namespace Day02
{
    
uint64_t GetNumberOfDigits(uint64_t i_number)
{
    uint64_t digits = 0;
    while (i_number > 0)
    {
        digits++;
        i_number = i_number/10;
    }
    return digits;
}

uint64_t ComputeHalfNumber(uint64_t i_number)
{
    uint64_t numberOfDigits = GetNumberOfDigits(i_number);
    if (numberOfDigits%2 == 1)
    {
        return std::pow(10, numberOfDigits/2);
    }
    return i_number/std::pow(10, numberOfDigits/2);
}

void ComputeInvalidIds(uint64_t i_begin, uint64_t i_end, std::unordered_set<uint64_t>& o_invalidIds)
{
    std::cout << i_begin << " -- " << i_end << "\n";
    const uint64_t halfBegin = ComputeHalfNumber(i_begin);
    const uint64_t halfEnd = ComputeHalfNumber(i_end);
    //std::println("begin {}, end {}", halfBegin, halfEnd);
    for (uint64_t halfNumber = halfBegin; halfNumber <= halfEnd; ++halfNumber)
    {
        //std::println("try {}", halfNumber);
        const uint64_t digits = GetNumberOfDigits(halfNumber);
        const uint64_t fullNumber = halfNumber*std::pow(10, digits)+halfNumber;
        if (i_begin <= fullNumber && fullNumber <= i_end)
        {
            std::cout << fullNumber << "\n";
            o_invalidIds.emplace(fullNumber);
        }
        if (fullNumber > i_end)
        {
            break;
        }
    }
}

static const std::vector<std::array<uint64_t,2>> test_input = {{99, 1010}};

void Problem1()
{
    auto& vectorInput = test_input;
    std::unordered_set<uint64_t> invalidIds;
    for (const auto& pair : vectorInput)
    {
        ComputeInvalidIds(pair[0], pair[1], invalidIds);
    }
    const uint64_t result = std::accumulate(std::begin(invalidIds),
                                            std::end(invalidIds),
                                            0);
    std::cout << "Sum: " << result << "\n";
}

}