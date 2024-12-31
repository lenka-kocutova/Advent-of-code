/*
* Part 1
One report per line
Each report is a list of levels

Report is safe if all levels are either increasing or decreasing
Adjacenty level value diff 1-3

*/

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

void Day2()
{
    std::ifstream file("Day2.txt");
    std::string line;
    std::vector<std::vector<int>> reports;
    while (std::getline(file, line))
    {
        auto words = LineIntoWords(line);
        std::vector<int> levels;
        std::ranges::transform(words, std::back_inserter(levels), [](const std::string& level) {return std::stoi(level); });
        reports.emplace_back(std::move(levels));
    }

    auto correctPair = [](const auto& pair)
        {
            int result = std::abs(std::get<0>(pair) - std::get<1>(pair));
            return result >= 1 && result <= 3;
        };
    auto correctReport = [correctPair](const auto& report)
        {
            if (not std::ranges::is_sorted(report, std::less()) and not std::ranges::is_sorted(report, std::greater()))
            {
                return false;
            }
            auto adjacentReport = report | std::views::adjacent<2>;
            return std::ranges::all_of(adjacentReport, correctPair);
        };

    // Part 1
    auto filteredReportsView = reports | std::views::filter(correctReport);
    auto count = std::ranges::distance(filteredReportsView);
    std::println("{}", count);


    // Part 2 - use brute force as previous attempts were unsucessful
    auto correctReportAfterModif = [correctReport](const auto& report)
        {
            if (correctReport(report))
            {
                return true;
            }
            for (size_t index = 0; index < report.size(); ++index)
            {
                auto newReport = report;
                newReport.erase(newReport.begin()+ index);
                if (correctReport(newReport))
                {
                    return true;
                }
            }
            return false;
        };

    auto filteredReportsView2 = reports | std::views::filter(correctReportAfterModif);
    auto count2 = std::ranges::distance(filteredReportsView2);
    std::println("{}", count2);

}
