#include <numeric>
#include <print>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include "Inputs/Day02.h"

namespace Day02 {

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

uint64_t GetNumberOfDigits(uint64_t i_number, uint32_t i_numberOfDigits)
{
    uint64_t totalNumberOfDigits = GetNumberOfDigits(i_number);
    if (totalNumberOfDigits < i_numberOfDigits)
    {
        return 1;
    }
    return i_number/std::pow(10, (totalNumberOfDigits-i_numberOfDigits));
}


void ComputeInvalidIdsPt1(uint64_t i_begin, uint64_t i_end, std::unordered_set<uint64_t>& invalidNumbers)
{
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
            //std::println("invalid {}", fullNumber);
            invalidNumbers.emplace(fullNumber);
        }
    }
}

void ComputeInvalidIdSumPt2(uint64_t i_begin, uint64_t i_end, std::unordered_set<uint64_t>& invalidNumbers)
{
    //std::println("begin {}, end {}", i_begin, i_end);
    int b;
    uint64_t digitsBegin = GetNumberOfDigits(i_begin);
    uint64_t digitsEnd = GetNumberOfDigits(i_end);
    if (digitsBegin%2 == 1)
    {
        ++digitsBegin;
    }
    if (digitsEnd%2 == 1)
    {
        ++digitsEnd;
    }
    for (uint32_t currentNumberOfDigits = 1; currentNumberOfDigits <= digitsEnd/2; ++currentNumberOfDigits)
    {
        //const uint64_t end = GetNumberOfDigits(i_end, currentNumberOfDigits);
        const uint64_t currentExponent = std::pow(10, currentNumberOfDigits);
        //std::println("current number of digits {}, begin {}, ", currentNumberOfDigits, begin);
        for (uint64_t currentSequence = currentExponent/10; currentSequence < currentExponent; ++currentSequence)
        {
            uint64_t currentNumber = currentSequence*currentExponent+currentSequence;
            if (currentNumber > i_end)
            {
                break;
            }
            //std::println("currentNumber {}", currentNumber);
            while (currentNumber < i_begin)
            {
                currentNumber = currentNumber*currentExponent+currentSequence;
            }
            while (currentNumber <= i_end)
            {
                if (i_begin <= currentNumber && currentNumber <= i_end)
                {
                    //std::println("invalid {}", currentNumber);
                    invalidNumbers.emplace(currentNumber);
                }
                currentNumber = currentNumber*currentExponent+currentSequence;
            }
        }
    }
}

void ComputeInvalidIdsBruteforcePt1(uint64_t i_begin, uint64_t i_end, std::unordered_set<uint64_t>& invalidNumbers)
{
    //uint64_t result = 0;
    //std::println("begin {}, end {}", halfBegin, halfEnd);
    for (uint64_t number = i_begin; number <= i_end; ++number)
    {
        const uint64_t numberOfDigits = GetNumberOfDigits(number);
        if (numberOfDigits%2 == 1)
        {
            continue;
        }
        const uint64_t exp = std::pow(10,numberOfDigits/2);
        const uint64_t upperHalf = number/exp;
        const uint64_t lowerHalf = number - (upperHalf*exp);
        if (upperHalf == lowerHalf)
        {
            std::cout << number << "\n";
            invalidNumbers.emplace(number);
        }
    }
    //return result;
}

void ComputeInvalidIdsPt2(uint64_t i_begin, uint64_t i_end, std::unordered_set<uint64_t>& invalidNumbers)
{
    //std::println("begin {}, end {}", i_begin, i_end);
    int b;
    uint64_t digitsBegin = GetNumberOfDigits(i_begin);
    uint64_t digitsEnd = GetNumberOfDigits(i_end);
    if (digitsBegin%2 == 1)
    {
        ++digitsBegin;
    }
    if (digitsEnd%2 == 1)
    {
        ++digitsEnd;
    }
    for (uint32_t currentNumberOfDigits = 1; currentNumberOfDigits <= digitsEnd/2; ++currentNumberOfDigits)
    {
        //const uint64_t end = GetNumberOfDigits(i_end, currentNumberOfDigits);
        const uint64_t currentExponent = std::pow(10, currentNumberOfDigits);
        //std::println("current number of digits {}, begin {}, ", currentNumberOfDigits, begin);
        for (uint64_t currentSequence = currentExponent/10; currentSequence < currentExponent; ++currentSequence)
        {
            uint64_t currentNumber = currentSequence*currentExponent+currentSequence;
            if (currentNumber > i_end)
            {
                break;
            }
            //std::println("currentNumber {}", currentNumber);
            while (currentNumber < i_begin)
            {
                currentNumber = currentNumber*currentExponent+currentSequence;
            }
            while (currentNumber <= i_end)
            {
                if (i_begin <= currentNumber && currentNumber <= i_end)
                {
                    //std::println("invalid {}", currentNumber);
                    invalidNumbers.emplace(currentNumber);
                }
                currentNumber = currentNumber*currentExponent+currentSequence;
            }
        }
    }
}

void Problem1()
{
    static const std::vector<std::array<uint64_t,2>> test_input = {{99, 1010}};
    auto& vectorInput = input;
    std::unordered_set<uint64_t> invalidIds;
    for (const auto& pair : vectorInput)
    {
        ComputeInvalidIdsPt1(pair[0], pair[1], invalidIds);
    }

    const uint64_t result = std::accumulate(std::begin(invalidIds),
                                            std::end(invalidIds),
                                            uint64_t{0});
    std::cout << "Sum: " << result << "\n";
}

void Problem2()
{
    static const std::vector<std::array<uint64_t,2>> test_input = {{99, 1010}};
    auto& vectorInput = input;
    std::unordered_set<uint64_t> invalidIds;
    for (const auto& pair : vectorInput)
    {
        ComputeInvalidIdsPt2(pair[0], pair[1], invalidIds);
    }
    const uint64_t result = std::accumulate(std::begin(invalidIds),
                                            std::end(invalidIds),
                                            uint64_t{0});
    std::cout << "Sum: " << result << "\n";
}

}