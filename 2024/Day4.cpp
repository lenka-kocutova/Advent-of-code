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
#include <numeric>
#include <exception>
#include <array>



void Day4()
{
    static const std::string xmas = "XMAS";
    std::optional<size_t> matrixSize;
    std::vector<std::string> lines;
    {
        std::ifstream file("Day4.txt");
        std::string line;
        while (std::getline(file, line))
        {
            if (!matrixSize.has_value())
            {
                matrixSize = line.size();
            }
            if (matrixSize != line.size())
            {
                throw std::exception();
            }
            lines.emplace_back(line);
        }
    }

    // Part 1 - Find all XMAS
    size_t counter2 = 0;
    for (size_t i = 0; i < *matrixSize; ++i)
    {
        for (size_t j = 0; j < *matrixSize; ++j)
        {
            if (lines[i][j] != 'X')
            {
                continue;
            }

            struct DirInfo
            {
                int stepX = 0;
                int stepY = 0;
                bool found = true;
            };

            std::array<DirInfo, 8> dirInfo = { DirInfo{ 1, 0}, DirInfo{-1, 0}, DirInfo{ 0, 1}, DirInfo{ 0,-1},
                                               DirInfo{ 1, 1}, DirInfo{-1, 1}, DirInfo{ 1,-1}, DirInfo{-1,-1} };

            for (auto [index, letter] : std::views::enumerate(std::vector{'M', 'A', 'S'}))
            {
                for (auto& dir : dirInfo)
                {
                    if (dir.found)
                    {
                        long long xCoord = i + dir.stepX*(index + 1);
                        long long yCoord = j + dir.stepY*(index + 1);
                        if(xCoord < 0 || xCoord >= *matrixSize || yCoord < 0 || yCoord >= *matrixSize)
                        {
                            dir.found = false;
                            continue;
                        }
                        dir.found = (lines[xCoord][yCoord] == letter);
                    }
                }
            }

            counter2 += std::ranges::count_if(dirInfo, [](const auto& dir) {return dir.found; });
        }
    }

    std::println("Count of XMAS: {}", counter2);

    // Part 2 - find cross MAS
    size_t counter1 = 0;
    for (size_t i = 1; i < *matrixSize - 1; ++i)
    {
        for (size_t j = 1; j < *matrixSize - 1; ++j)
        {
            if (lines[i][j] == 'A')
            {
                if (((lines[i-1][j-1] == 'M' && lines[i+1][j+1] == 'S') ||
                     (lines[i-1][j-1] == 'S' && lines[i+1][j+1] == 'M')) &&
                    ((lines[i-1][j+1] == 'M' && lines[i+1][j-1] == 'S') ||
                     (lines[i-1][j+1] == 'S' && lines[i+1][j-1] == 'M')))
                {
                    counter1++;
                }
            }
        }
    }

    std::println("Count of X-MAS: {}", counter1);
}