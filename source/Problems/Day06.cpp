#include "Inputs/Day06.h"
#include <iostream>
#include <functional>

namespace Day06
{

uint64_t Sum(uint64_t i_first, uint64_t i_second)
{
    return i_first+i_second;
}

uint64_t Product(uint64_t i_first, uint64_t i_second)
{
    return i_first*i_second;
}

void Problem1()
{
    auto& currentInput = input;

    uint64_t result = 0;
    for (size_t idx = 0; idx < currentInput.numbers[0].size(); ++idx)
    {
        uint64_t partialResult = currentInput.numbers[0][idx];
        std::function<uint64_t(uint64_t,uint64_t)> operation = currentInput.operations[idx] == '+' ? Sum : Product;
        for (size_t jdx = 1; jdx < currentInput.numbers.size(); ++jdx)
        {
            partialResult = operation(partialResult, currentInput.numbers[jdx][idx]);
        }
        result += partialResult;
    }
    std::cout << "result: " << result << "\n" ;
}

void Problem2()
{
    auto& currentInput = input;

    size_t currentNumberIdx = 0;
    size_t currentIndex = 0;
    uint64_t result = 0;
    while (currentIndex < currentInput.strNumbers[0].size())
    {
        std::function<uint64_t(uint64_t,uint64_t)> operation = currentInput.operations[currentNumberIdx] == '+' ? Sum : Product;
        uint64_t partialResult = 0;
        uint64_t numberToBuild = 0;
        while (currentIndex < currentInput.strNumbers[0].size()) {
            numberToBuild = 0;
            for (size_t rowIdx = 0; rowIdx < currentInput.strNumbers.size(); ++rowIdx)
            {
                const char currentChar = currentInput.strNumbers[rowIdx][currentIndex];
                if (currentChar != ' ')
                {
                    numberToBuild = (numberToBuild * 10) + (currentChar-'0');
                }
            }
            //std::cout << numberToBuild << "\n";
            ++currentIndex;
            if (numberToBuild == 0)
            {
                break;
            }
            if (partialResult == 0)
            {
                partialResult = numberToBuild;
            }
            else
            {
                partialResult = operation(partialResult, numberToBuild);
            }
        }
        ++currentNumberIdx;
        
        result += partialResult;
    }
    std::cout << "result: " << result << "\n" ;
}
}