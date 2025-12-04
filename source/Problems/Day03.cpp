#include "Inputs/Day03.h"
#include <cstdint>
#include <numeric>
#include <iostream>

namespace Day03
{

size_t GetNDigitsMaxNumber(std::string_view i_numbers, uint8_t i_quantityOfNumbers)
{
    //std::set<size_t> indices;
    int64_t result = 0;
    int64_t lastIndex = -1;
    while (i_quantityOfNumbers > 0)
    {
        //std::println("{} - last number {} - size {}", i_quantityOfNumbers, (i_numbers.size()-i_quantityOfNumbers+1), i_numbers.size());
        size_t maxIndex = i_numbers.size();
        for (size_t idx = lastIndex+1; idx < (i_numbers.size()-i_quantityOfNumbers+1); ++idx)
        {
            if ((maxIndex == i_numbers.size() || i_numbers[idx] > i_numbers[maxIndex]))
            {
                maxIndex = idx;
            }
        }
        result = result*10+(i_numbers[maxIndex]-'0');
        lastIndex = maxIndex;
        --i_quantityOfNumbers;
    }
    //std::println("{}",result);
    return result;
}

void Problem1()
{
    std::cout << std::accumulate(std::begin(input), std::end(input), size_t{0}, [](size_t sum, const std::string& str){return sum + GetNDigitsMaxNumber(str, 2);}) << "\n";
}

void Problem2()
{
    std::cout << std::accumulate(std::begin(input), std::end(input), size_t{0}, [](size_t sum, const std::string& str){return sum + GetNDigitsMaxNumber(str, 12);}) << "\n";
}

}