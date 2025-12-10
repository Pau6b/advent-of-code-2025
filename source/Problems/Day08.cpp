#include "Inputs/Day08.h"
#include <print>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <iterator>

namespace Day08
{

    struct Distance
    {
        size_t firstPoint;
        size_t secondPoint;
        uint64_t distance;
    };

    uint64_t ComputeDistanceSq(const Point &i_left, const Point &i_right)
    {
        const int64_t distx = i_left.x - i_right.x;
        const int64_t disty = i_left.y - i_right.y;
        const int64_t distz = i_left.z - i_right.z;

        return distx * distx + disty * disty + distz * distz;
    }

    std::vector<Distance> ComputeAllDistances(std::vector<Point> i_points)
    {
        const size_t quantityOfPoints = i_points.size();

        std::vector<Distance> result;
        result.reserve(quantityOfPoints * quantityOfPoints);

        for (size_t idx = 0; idx < quantityOfPoints; ++idx)
        {
            for (size_t jdx = idx + 1; jdx < quantityOfPoints; ++jdx)
            {
                result.emplace_back(Distance{idx, jdx, ComputeDistanceSq(i_points[idx], i_points[jdx])});
            }
        }
        return result;
    }

    struct Group
    {
        std::vector<size_t> points;
    };

    int64_t FindPointInGroup(const std::vector<Group> &i_groups, size_t i_pointIdx)
    {
        auto it = std::find_if(std::begin(i_groups),
                               std::end(i_groups),
                               [i_pointIdx](const Group &i_group)
                               { return std::find(std::begin(i_group.points), std::end(i_group.points), i_pointIdx) != std::end(i_group.points); });
        if (it == std::end(i_groups))
        {
            return -1;
        }
        return std::distance(std::begin(i_groups), it);
    }

    void Problem1()
    {
        auto &currentInput = input;
        const size_t k_numberOfPointsToJoin = 1000;

        std::vector<Distance> allDistances = ComputeAllDistances(currentInput);
        std::sort(std::begin(allDistances), std::end(allDistances), [](const auto &i_lhs, const auto &i_rhs)
                  { return i_lhs.distance < i_rhs.distance; });

        size_t currentIndex = 0;
        std::vector<Group> groups;
        while (currentIndex < k_numberOfPointsToJoin)
        {
            const Distance &currentDistance = allDistances[currentIndex];
            Point &firstPoint = currentInput[currentDistance.firstPoint];
            Point &secondPoint = currentInput[currentDistance.secondPoint];
            const int64_t firstPointGroupIdx = FindPointInGroup(groups, currentDistance.firstPoint);
            const int64_t secondPointGroupIdx = FindPointInGroup(groups, currentDistance.secondPoint);

            if (firstPointGroupIdx == -1 && secondPointGroupIdx == -1)
            {
                groups.emplace_back(Group{{currentDistance.firstPoint, currentDistance.secondPoint}});
            }
            else if (firstPointGroupIdx == -1 || secondPointGroupIdx == -1)
            {
                const size_t &grouplessPointIdx = firstPointGroupIdx == -1 ? currentDistance.firstPoint : currentDistance.secondPoint;
                Point &grouplessPoint = currentInput[grouplessPointIdx];
                const size_t &groupedPointIdx = firstPointGroupIdx == -1 ? currentDistance.secondPoint : currentDistance.firstPoint;
                const size_t &groupedPointGroupIdx = firstPointGroupIdx == -1 ? secondPointGroupIdx : firstPointGroupIdx;
                const Point &groupedPoint = firstPointGroupIdx == -1 ? secondPoint : firstPoint;
                Group &group = groups[groupedPointGroupIdx];
                group.points.emplace_back(grouplessPointIdx);
            }
            else if (firstPointGroupIdx != -1 && secondPointGroupIdx != -1 && firstPointGroupIdx != secondPointGroupIdx)
            {
                Group &firstGroup = groups[firstPointGroupIdx];
                Group &secondGroup = groups[secondPointGroupIdx];
                firstGroup.points.insert(std::end(firstGroup.points), std::begin(secondGroup.points), std::end(secondGroup.points));
                groups.erase(std::begin(groups) + secondPointGroupIdx);
            }
            ++currentIndex;
        }
        std::sort(std::begin(groups), std::end(groups), [](const auto &i_lhs, const auto &i_rhs)
                  { return i_lhs.points.size() > i_rhs.points.size(); });
        std::println("result {}", groups[0].points.size() * groups[1].points.size() * groups[2].points.size());
    }

    void Problem2()
    {
        auto &currentInput = input;

        std::vector<Distance> allDistances = ComputeAllDistances(currentInput);
        std::sort(std::begin(allDistances), std::end(allDistances), [](const auto &i_lhs, const auto &i_rhs)
                  { return i_lhs.distance < i_rhs.distance; });

        size_t currentIndex = 0;
        std::vector<Group> groups;
        while (currentIndex < allDistances.size())
        {
            const Distance &currentDistance = allDistances[currentIndex];
            Point &firstPoint = currentInput[currentDistance.firstPoint];
            Point &secondPoint = currentInput[currentDistance.secondPoint];
            const int64_t firstPointGroupIdx = FindPointInGroup(groups, currentDistance.firstPoint);
            const int64_t secondPointGroupIdx = FindPointInGroup(groups, currentDistance.secondPoint);

            if (firstPointGroupIdx == -1 && secondPointGroupIdx == -1)
            {
                groups.emplace_back(Group{{currentDistance.firstPoint, currentDistance.secondPoint}});
            }
            else if (firstPointGroupIdx == -1 || secondPointGroupIdx == -1)
            {
                const size_t &grouplessPointIdx = firstPointGroupIdx == -1 ? currentDistance.firstPoint : currentDistance.secondPoint;
                Point &grouplessPoint = currentInput[grouplessPointIdx];
                const size_t &groupedPointIdx = firstPointGroupIdx == -1 ? currentDistance.secondPoint : currentDistance.firstPoint;
                const size_t &groupedPointGroupIdx = firstPointGroupIdx == -1 ? secondPointGroupIdx : firstPointGroupIdx;
                const Point &groupedPoint = firstPointGroupIdx == -1 ? secondPoint : firstPoint;
                Group &group = groups[groupedPointGroupIdx];
                group.points.emplace_back(grouplessPointIdx);

                if (groups.size() == 1 && groups[0].points.size() == currentInput.size())
                {
                    std::println("result: {}, {} - {}", firstPoint.x * secondPoint.x, firstPoint.x, secondPoint.x);
                    break;
                }
            }
            else if (firstPointGroupIdx != -1 && secondPointGroupIdx != -1 && firstPointGroupIdx != secondPointGroupIdx)
            {
                Group &firstGroup = groups[firstPointGroupIdx];
                Group &secondGroup = groups[secondPointGroupIdx];
                firstGroup.points.insert(std::end(firstGroup.points), std::begin(secondGroup.points), std::end(secondGroup.points));
                groups.erase(std::begin(groups) + secondPointGroupIdx);
                if (groups.size() == 1 && groups[0].points.size() == currentInput.size())
                {
                    std::println("result: {}, {} - {}", firstPoint.x * secondPoint.x, firstPoint.x, secondPoint.x);
                    break;
                }
            }
            ++currentIndex;
        }
    }

}