#include "Reusable.h"
#include "AoC2024.h"

#include <fstream>
#include <string>
#include <sstream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <print>
#include <tuple>
#include <map>
#include <set>
#include <optional>
#include <iostream>
#include <numeric>
#include <exception>
#include <array>



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
            if (isRules)
            {
                rules.emplace_back(line);
            }
            else
            {
                orders.emplace_back(line);
            }
            if (line.empty())
            {
                isRules = false;
            }
        }
    }

    // Set rules
    for (std::string rule : rules)
    {
        auto pairs = rule | std::views::split('|') | std::views::adjacent<2>;
        for (auto pair : pairs)
        {
            auto val = std::get<0>(pair);
            std::string result1(val.begin(), val.end());
            unsigned int result3 = std::stoul(result1);
            auto dep = std::get<1>(pair);
            std::string result2(dep.begin(), dep.end());
            unsigned int result4 = std::stoul(result2);
            mapRules[result3].emplace(result4);
        }
    }

    std::vector<std::vector<unsigned int>> orderList;
    for (const auto& order : orders)
    {
        auto& currentOrder = orderList.emplace_back();
        auto orderPages = order | std::views::split(',');
        for (auto orderPage : orderPages)
        {
            std::string result(orderPage.begin(), orderPage.end());
            unsigned int page = std::stoul(result);
            currentOrder.emplace_back(page);
        }
    }

    // Part 1 - Sum up the middle values from correct orders
    unsigned long long sumCorrect = 0;
    for (const auto& order : orderList)
    {
        bool currentOk = true;
        for (auto itPage = order.begin(); itPage != order.end(); ++itPage)
        {
            const auto& currentPageSuccessors = mapRules[*itPage];
            for (auto itSuccessingPage = std::next(itPage); itSuccessingPage != order.end(); ++itSuccessingPage)
            {
                if (currentPageSuccessors.find(*itSuccessingPage) == currentPageSuccessors.end())
                {
                    currentOk = false;
                    break;
                }
            }
            if (!currentOk)
            {
                break;
            }
        }
        if (currentOk)
        {
            if (order.size() % 2 == 0)
            {
                int x = 5;
            }
            auto it = order.begin() + order.size()/2;
            sumCorrect += *it;
            std::cout << *it << std::endl;
        }
    }
    std::cout << sumCorrect << std::endl;

    // Part 2 - Sum up the middle values from incorrect orders after correcting them
    unsigned long long sumIncorrect = 0;
    for (const auto& order : orderList)
    {
        bool currentOk = true;
        for (auto itPage = order.begin(); itPage != order.end(); ++itPage)
        {
            const auto& currentPageSuccessors = mapRules[*itPage];
            for (auto itSuccessingPage = std::next(itPage); itSuccessingPage != order.end(); ++itSuccessingPage)
            {
                if (currentPageSuccessors.find(*itSuccessingPage) == currentPageSuccessors.end())
                {
                    currentOk = false;
                    break;
                }
            }
            if (!currentOk)
            {
                break;
            }
        }
        if (!currentOk)
        {
            auto orderCopy = order;

            while (!currentOk)
            {
                currentOk = true;
                for (auto itPage = orderCopy.begin(); itPage != orderCopy.end(); ++itPage)
                {
                    const auto& currentPageSuccessors = mapRules[*itPage];
                    for (auto itSuccessingPage = std::next(itPage); itSuccessingPage != orderCopy.end(); ++itSuccessingPage)
                    {
                        if (currentPageSuccessors.find(*itSuccessingPage) == currentPageSuccessors.end())
                        {
                            currentOk = false;
                            std::iter_swap(itPage, itSuccessingPage);
                            break;
                        }
                    }
                    if (!currentOk)
                    {
                        break;
                    }
                }
            }

            if (orderCopy.size() % 2 == 0)
            {
                int x = 5;
            }
            auto it = orderCopy.begin() + orderCopy.size() / 2;
            sumIncorrect += *it;
            std::cout << *it << std::endl;
        }
    }
    std::cout << sumIncorrect << std::endl;
}