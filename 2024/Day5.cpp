#include "Reusable.h"
#include "AoC2024.h"

#include <fstream>
#include <string>
#include <sstream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <numeric>
#include <print>


bool ArePagesOrdered(const std::vector<unsigned int>& order, const std::map<unsigned int, std::set<unsigned int>>& mapRules)
{
    for (auto itPage = order.begin(); itPage != order.end(); ++itPage)
    {
        unsigned int page = *itPage;
        const auto& currentPageSuccessors = mapRules.at(page);
        for (auto itSuccessingPage = std::next(itPage); itSuccessingPage != order.end(); ++itSuccessingPage)
        {
            if (currentPageSuccessors.find(*itSuccessingPage) == currentPageSuccessors.end())
            {
                return false;
            }
        }
    }
    return true;
}

void Day5()
{
    std::map<unsigned int, std::set<unsigned int>> mapRules;
    std::vector<std::string> rules, orders;
    {
        std::ifstream file("Day5.txt");
        std::string line;
        bool isRules = true;
        while (std::getline(file, line))
        {
            auto& current = isRules ? rules : orders;
            current.emplace_back(line);
            if (line.empty())
            {
                isRules = false;
            }
        }
    }

    // Set rules
    for (const std::string& rule : rules)
    {
        auto pairs = rule | std::views::split('|') | std::views::adjacent<2>;
        for (auto [predecessor, successor] : pairs)
        {
            unsigned int predecessorPage = std::stoul(std::string(predecessor.begin(), predecessor.end()));
            unsigned int successorPage = std::stoul(std::string(successor.begin(), successor.end()));
            mapRules[predecessorPage].emplace(successorPage);
        }
    }

    // Define orders of pages
    std::vector<std::vector<unsigned int>> orderList;
    for (const auto& order : orders)
    {
        auto& currentOrder = orderList.emplace_back();
        auto orderPages = order | std::views::split(',');
        std::ranges::transform(orderPages, std::back_inserter(currentOrder), [](auto orderPage) {return std::stoul(std::string(orderPage.begin(), orderPage.end())); });
    }

    // Part 1 - Sum up the middle values from correct orders
    auto orderedList = orderList | std::views::filter([&mapRules](const std::vector<unsigned int>& order)
    {
        return ArePagesOrdered(order, mapRules);
    });

    unsigned long long sumCorrect = std::transform_reduce(std::begin(orderedList), std::end(orderedList), 0ull, std::plus{}, [](const std::vector<unsigned int>& order)
    {
        auto itMiddle = order.begin() + order.size() / 2;
        return *itMiddle;
    });
    std::println("{}", sumCorrect);

    // Part 2 - Sum up the middle values from incorrect orders after correcting them
    auto notOrderedList = orderList | std::views::filter([&mapRules](const std::vector<unsigned int>& order)
    {
        return !ArePagesOrdered(order, mapRules);
    });

    unsigned long long sumIncorrect = std::transform_reduce(std::begin(notOrderedList), std::end(notOrderedList), 0ull, std::plus{}, [&mapRules](const std::vector<unsigned int>& order)
    {
        auto orderCopy = order;
        std::ranges::sort(orderCopy, [&mapRules](auto page1, auto page2)
        {
            const auto& currentPageSuccessors = mapRules[page1];
            return currentPageSuccessors.find(page2) != currentPageSuccessors.end();
        });

        auto itMiddle = orderCopy.begin() + orderCopy.size() / 2;
        return *itMiddle;
    });

    std::println("{}", sumIncorrect);
}