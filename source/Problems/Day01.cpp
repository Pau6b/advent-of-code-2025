#include <cstdint>
#include <iostream>
#include <sstream>
#include "Inputs/Day01.h"

namespace Day01
{

void Problem1()
{
    std::stringstream inputss(input);
    char command;
    int32_t steps;

    int32_t counter = 50;
    int32_t result = 0;

    while (inputss >> command >> steps)
    {
        if (command == 'L')
        {
            steps *= -1;
        }
        counter = ((counter + steps) % 100 + 100) % 100;
        if (counter == 0)
        {
            result++;
        }
    }
    std::cout << counter << " -- " << result << "\n";
}

void Problem2()
{
    std::stringstream inputss(input);
    char command;
    int32_t steps;

    int32_t counter = 50;
    int32_t result = 0;

    while (inputss >> command >> steps)
    {
        if (command == 'L')
        {
            steps *= -1;
        }
        const bool counterWasZero = counter == 0;
        counter = counter + steps;
        if (counter >= 100)
        {
            result += counter/100;
        }
        else if (counter <= 0)
        {
            if (!counterWasZero)
            {
                result++;
            }
            result -= counter/100;
        }
        counter = (counter % 100 + 100) % 100;
        
    }
    std::cout << counter << " -- " << result << "\n";
}
}
