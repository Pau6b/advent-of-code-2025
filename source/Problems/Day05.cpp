#include "Inputs/Day05.h"
#include <iostream>
#include <cstdint>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <numeric>

namespace Day05
{

    std::map<uint64_t, uint64_t> FixRange(std::vector<std::array<uint64_t, 2>> &ranges)
    {
        std::map<uint64_t, uint64_t> rangesMap;
        for (auto &range : ranges)
        {
            auto it = rangesMap.try_emplace(range[0], range[1]);
            if (!it.second)
            {
                it.first->second = std::max(range[1], it.first->second);
            }
        }

        for (auto it = std::begin(rangesMap); it != std::end(rangesMap);)
        {
            auto originalIt = it;
            ++it;
            while (it != std::end(rangesMap) && it->first <= originalIt->second)
            {
                originalIt->second = std::max(it->second, originalIt->second);
                it = rangesMap.erase(it);
            }
        }
        return rangesMap;
    }

    std::vector<uint64_t> Problem1Bruteforce()
    {
        auto &currentInput = input;

        std::vector<uint64_t> resultIngredients;

        auto result = std::count_if(std::begin(currentInput.ingredients),
                                    std::end(currentInput.ingredients),
                                    [&currentInput, &resultIngredients](uint64_t i_newValue)
                                    {
                                        bool result = std::any_of(std::begin(currentInput.ranges), std::end(currentInput.ranges),
                                                                  [i_newValue](auto &i_range)
                                                                  { return i_range[0] <= i_newValue && i_newValue <= i_range[1]; });
                                        if (result)
                                        {
                                            resultIngredients.emplace_back(i_newValue);
                                        }
                                        return result;
                                    });
        std::cout << result << "\n";
        return resultIngredients;
    }

    void Problem1()
    {
        auto &currentInput = input;
        std::map<uint64_t, uint64_t> ranges = FixRange(currentInput.ranges);

        auto result = std::count_if(std::begin(currentInput.ingredients),
                                    std::end(currentInput.ingredients),
                                    [&ranges](uint64_t i_newValue)
                                    {
                                        auto it = ranges.lower_bound(i_newValue);
                                        if (it != std::begin(ranges) && it->first != i_newValue)
                                        {
                                            --it;
                                        }
                                        const bool result = it->first <= i_newValue && i_newValue <= it->second;
                                        // std::println("{} {}", result ? "yes: " : "no: ", i_newValue);
                                        return result;
                                    });

        std::cout << "result: " << result << "\n";
    }


    void Problem2()
    {
        auto &currentInput = input;
        std::map<uint64_t, uint64_t> ranges = FixRange(currentInput.ranges);

        uint64_t numberOfFreshIngredients = std::accumulate(std::begin(ranges), std::end(ranges), uint64_t{0}, [](const uint64_t i_accumulated, const auto &kv)
                                                            {
                                                                std::cout << i_accumulated << " -- " << kv.second - kv.first + 1 << "\n"; 
                                                                return i_accumulated + (kv.second - kv.first) + 1;
                                                            });

        std::cout << "result : " << numberOfFreshIngredients << "\n";
    }

}
