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
#include <optional>
#include <iostream>
#include <iomanip>

void Day3()
{
    using std::operator""sv;
    constexpr auto delimiter{ "mul("sv };
    constexpr auto delimiter2{ ","sv };

    long long totalValue = 0;
    std::ifstream file("Day3.txt");
    std::string line;
    bool lastRemoved = false, lastRemoved1 = false;
    while (std::getline(file, line))
    {
        lastRemoved = lastRemoved1;
        std::string newLine;
        auto splitDo = line | std::views::split("do()"sv);
        for (auto x : splitDo)
        {
            if (lastRemoved)
            {
                lastRemoved = false;
                continue;
            }
            std::cout << std::endl;
            auto str = std::string(std::string_view(x));
            auto pos = str.find("don't()");
            std::string newString = (pos != std::string::npos) ? str.substr(0, pos) : str;
            std::cout << "Used: " << newString << std::endl;
            lastRemoved1 = (pos != std::string::npos);
            newLine += newString;
        }

        lastRemoved = lastRemoved1;

        auto instructions = newLine |
            std::views::split(delimiter) |
            std::views::filter([&totalValue](auto instruction)
                {
                    auto itFound = std::ranges::find(instruction, ')');
                    if (itFound == instruction.end())
                    {
                        std::cout << "Removed: mul(" << std::string_view(instruction) << std::endl;
                        return false;
                    }
                    std::string newStr(instruction.begin(), itFound);
                    auto itFound2 = std::ranges::find(newStr, ',');
                    if (itFound2 == newStr.end())
                    {
                        std::cout << "Removed: mul(" << std::string_view(instruction) << std::endl;
                        return false;
                    }
                    std::string number1(newStr.begin(), itFound2);
                    std::string number2(itFound2 + 1, newStr.end());
                    if (number1.empty() or number2.empty() or not std::ranges::all_of(number1, isdigit) or not std::ranges::all_of(number2, isdigit))
                    {
                        std::cout << "Removed: mul(" << std::string_view(instruction) << std::endl;
                        return false;
                    }
                    long long newValue = std::stol(number1) * std::stol(number2);
                    std::cout << "Used: mul(" << number1 << "," << number2 << ") = " << newValue << " + " << totalValue << " = " << totalValue + newValue << std::endl;
                    totalValue += newValue;

                    
                    return true;
                });
        std::ranges::for_each(instructions, [](auto x) {});
    }
    std::cout << totalValue << std::endl;
}