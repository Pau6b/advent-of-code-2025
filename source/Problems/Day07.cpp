#include "Inputs/Day07.h"
#include <iostream> 

namespace Day07
{

    void Problem1()
    {
        auto& currentInput = input;

        size_t result = 0;

        size_t firstPos = currentInput[0].find('S');
        currentInput[0][firstPos] = '|';
        for (size_t idx = 0; idx < currentInput.size()-1; ++idx)
        {
            size_t nidx = idx + 1;
            for (size_t jdx = 0; jdx < currentInput[idx].size(); ++jdx)
            {
                if (currentInput[idx][jdx] != '|')
                {
                    continue;
                }
                if (currentInput[nidx][jdx] == '.')
                {
                    currentInput[nidx][jdx] = '|';
                }
                if (currentInput[nidx][jdx] == '^')
                {
                    currentInput[nidx][jdx-1] = '|';
                    currentInput[nidx][jdx+1] = '|';
                    ++result;
                }
            }
        }

        for (size_t idx = 0; idx < currentInput.size(); ++idx)
        {
            std::cout << currentInput[idx] << "\n";
        }
        std::cout << "result: " << result << "\n";
    }

    size_t ComputeNumberOfPaths(const std::vector<std::string>& i_map, std::vector<std::vector<size_t>>& i_memoizer, size_t i_x, size_t i_y)
    {
        size_t x = i_x;
        while(x < i_map.size() && i_map[x][i_y] == '.')
        {
            ++x;
        }
        if (x == i_map.size())
        {
            i_memoizer[i_x][i_y] = 1;
            return 1;
        }
        if (i_memoizer[x][i_y-1] == 0)
        {
            ComputeNumberOfPaths(i_map, i_memoizer, x, i_y-1);
        }
        if (i_memoizer[x][i_y+1] == 0)
        {
            ComputeNumberOfPaths(i_map, i_memoizer, x, i_y+1);
        }
        i_memoizer[i_x][i_y] = i_memoizer[x][i_y-1] + i_memoizer[x][i_y+1];
        return i_memoizer[x][i_y-1] + i_memoizer[x][i_y+1];
    }

    void Problem2()
    {
        auto& currentInput = input;
        std::vector<std::vector<size_t>> memoizer(currentInput.size(), std::vector<size_t>(currentInput[0].size(),0));
        const size_t firstPos = currentInput[0].find('S');
        size_t result = ComputeNumberOfPaths(currentInput, memoizer, 0, firstPos);
        
        for (size_t idx = 0; idx < memoizer.size(); ++idx)
        {
            for (size_t jdx = 0; jdx < memoizer[0].size(); ++jdx)
            {
                std::cout << memoizer[idx][jdx] <<"-";
            }
            std::cout << "\n";
        }
        
        std::cout << "result: " << result << "\n";
    }
}