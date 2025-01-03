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
#include <iomanip>

void Day3()
{
    using std::operator""sv;
    constexpr auto mulInstruction{ "mul("sv };
    constexpr auto delimiter{ ","sv };

    long long totalValue = 0;
    std::ifstream file("Day3.txt");
    std::string line;
    bool startWithDont = false;
    while (std::getline(file, line))
    {
        // Part 2 - execute only mul instructions between do and dont instructions
        bool startWithDontLocal = startWithDont;
        std::string newLine;
        auto splitDo = line | std::views::split("do()"sv);
        for (auto dos : splitDo)
        {
            if (startWithDontLocal)
            {
                startWithDontLocal = false;
                continue;
            }
            auto stringAfterDo = std::string(std::string_view(dos));
            auto positionDont = stringAfterDo.find("don't()");
            std::string stringBetweenDoAndDont = (positionDont != std::string::npos) ? stringAfterDo.substr(0, positionDont) : stringAfterDo;
            std::println("Used: {}", stringBetweenDoAndDont);
            startWithDont = (positionDont != std::string::npos);
            newLine += stringBetweenDoAndDont;
        }

        // Part 1 - Sum result of all valid mul instructions
        auto instructions = newLine |
            std::views::split(mulInstruction) |
            std::views::filter([&totalValue](auto instruction)
                {
                    auto itFound = std::ranges::find(instruction, ')');
                    if (itFound == instruction.end())
                    {
                        std::println("Removed mul({}", std::string_view(instruction));
                        return false;
                    }
                    std::string newStr(instruction.begin(), itFound);
                    auto itFound2 = std::ranges::find(newStr, ',');
                    if (itFound2 == newStr.end())
                    {
                        std::println("Removed mul({}", std::string_view(instruction));
                        return false;
                    }
                    std::string number1(newStr.begin(), itFound2);
                    std::string number2(itFound2 + 1, newStr.end());
                    if (number1.empty() || number2.empty() || !std::ranges::all_of(number1, isdigit) || !std::ranges::all_of(number2, isdigit))
                    {
                        std::println("Removed mul({}", std::string_view(instruction));
                        return false;
                    }
                    long long newValue = std::stol(number1) * std::stol(number2);
                    std::println("Used mul({}, {}) = {} + {} = {}", number1, number2, newValue, totalValue, totalValue + newValue);
                    totalValue += newValue;
                    return true;
                });
        std::ranges::for_each(instructions, [](auto x) {});
    }
    std::println("{}", totalValue);
}