/*
* Part 1
Mark visited locations with star
Must be on first 50 visited places
List of locations is empty
First place - office is empty
Locations contain LocationID
2 groups making locationIDs

Pair up the numbers from 2 sets and mmeasure how far aparat they are
do not make unique, sort, pair from smallest to largest
foreach pair compute difference
sum the differences

Part 2
Foreach number in leftlist
Multiply it's value with the number of times it appears in the right list
*/

#include "Reusable.h"

#include <fstream>
#include <string>
#include <sstream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <print>
#include <tuple>

int main()
{
	std::ifstream file("Day1.txt");
    std::string line;
    std::vector<int> inputLeft, inputRight;
    while (std::getline(file, line))
    {
        auto words = LineIntoWords(line);
        inputLeft.emplace_back(std::stoi(words.at(0)));
        inputRight.emplace_back(std::stoi(words.at(1)));
    }

    std::ranges::sort(inputLeft);
    std::ranges::sort(inputRight);

    // Part 1
    auto resultView = std::views::zip_transform([](int valueLeft, int valueRight){
                          return std::abs(valueLeft - valueRight);
                       }, inputLeft, inputRight);
    auto result = std::ranges::fold_left(resultView, 0, std::plus{});
    std::println("{}", result);

    // Part 2
    auto multiplies = std::views::zip_transform([&inputRight](int valueLeft) {
                            return valueLeft * std::ranges::count(inputRight, valueLeft);
                      }, inputLeft);
    auto totalValue = std::ranges::fold_left(multiplies, 0, std::plus{});
    std::println("{}", totalValue);
}
