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
            if (not matrixSize.has_value())
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
    
    // Count horizontal
    std::cout << "Horizontal" << std::endl;
    size_t counter = SubstringCounter(lines, xmas);

    // Count reverse horizontal
    std::cout << "Reverse horizontal" << std::endl;
    std::vector<std::string> linesReverse = ReverseStrings(lines);
    counter += SubstringCounter(linesReverse, xmas);

    // Count vertical
    std::cout << "Vertical" << std::endl;
    std::vector<std::string> linesVertical(*matrixSize, "");
    for (const auto& line : lines)
    {
        size_t index = 0;
        for (char a : line)
        {
            linesVertical[index++] += a;
        }
    }
    counter += SubstringCounter(linesVertical, xmas);

    // Count reverse vertical
    std::cout << "Reverse vertical" << std::endl;
    std::vector<std::string> linesReverseVertical = ReverseStrings(linesVertical);
    counter += SubstringCounter(linesReverseVertical, xmas);

    // Count diagonal
    std::cout << "Diagonal" << std::endl;
    std::vector<std::string> linesDiagonal(2*(*matrixSize)-1, "");
    for(size_t i = 0; i < 2 * (*matrixSize)-1 ; ++i)
    {
        for (size_t j = 0; j <= i; ++j)
        {
            if (j >= matrixSize || i - j >= matrixSize)
            {
                linesDiagonal[i] += " ";
            }
            else
            {
                linesDiagonal[i] += lines[j][i - j];
            }
        }
    }
    counter += SubstringCounter(linesDiagonal, xmas);

    // Count reverse diagonal
    std::cout << "Reverse diagonal" << std::endl;
    std::vector<std::string> linesDiagonalReverse = ReverseStrings(linesDiagonal);
    counter += SubstringCounter(linesDiagonalReverse, xmas);

    // Count cross diagonal
    std::cout << "Cross diagonal" << std::endl;
    std::vector<std::string> linesCrossDiagonal(2 * (*matrixSize) - 1, "");
    for (size_t i = 0; i < 2 * (*matrixSize) - 1; ++i)
    {
        for (size_t j = 0; j <= i; ++j)
        {
            if (j >= matrixSize || i - j >= matrixSize)
            {
                linesCrossDiagonal[i] += " ";
            }
            else
            {
                size_t index2 = *matrixSize - (i - j) - 1;
                linesCrossDiagonal[i] += lines[j][index2];
            }
        }
    }
    counter += SubstringCounter(linesCrossDiagonal, xmas);

    // Count cross reverse diagonal
    std::cout << "Reverse cross diagonal" << std::endl;
    std::vector<std::string> linesCrossDiagonalReverse = ReverseStrings(linesCrossDiagonal);
    counter += SubstringCounter(linesCrossDiagonalReverse, xmas);

    std::cout << counter << std::endl;

    // Part 2 - find cross 

    size_t counter1 = 0;
    for (size_t i = 1; i < *matrixSize - 1; ++i)
    {
        for (size_t j = 1; j < *matrixSize - 1; ++j)
        {
            if (lines[i][j] == 'A')
            {
                std::vector<std::vector<char>> neighbours{ { lines[i - 1][j - 1], lines[i - 1][j + 1] },
                                                           { lines[i + 1][j - 1], lines[i + 1][j + 1]} };

                if (((neighbours[0][0] == 'M' && neighbours[1][1] == 'S') ||
                     (neighbours[0][0] == 'S' && neighbours[1][1] == 'M')) &&
                    ((neighbours[0][1] == 'M' && neighbours[1][0] == 'S') ||
                     (neighbours[0][1] == 'S' && neighbours[1][0] == 'M')))
                {
                    counter1++;
                }
            }
        }
    }

    std::cout << "Count of X-MAS: " << counter1 << std::endl;
}