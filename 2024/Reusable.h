#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <iostream>

inline std::vector<std::string> LineIntoWords(const std::string& sentence)
{
    std::istringstream iss(sentence);
    return std::vector<std::string>(
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>{});
}

inline size_t SubstringCounter(const std::string& string, const std::string& substring)
{
    size_t counter = 0;
    size_t position = string.find(substring);
    while (position != std::string::npos)
    {
        ++counter;
        position = string.find(substring, position + 1);
    }
    return counter;
}

inline size_t SubstringCounter(const std::vector<std::string>& strings, const std::string& substring)
{
    for (const auto& s : strings)
    {
        std::cout << s << std::endl;
    }
    std::cout << std::endl;
    std::vector<size_t> valuesPerLine;
    std::transform(strings.begin(), strings.end(), std::back_inserter(valuesPerLine), [&substring](const std::string& str) -> size_t {return SubstringCounter(str, substring); });
    size_t count = std::reduce(valuesPerLine.begin(), valuesPerLine.end());
    std::cout << "Count: " << count << std::endl;
    return count;
}

inline std::string ReverseString(const std::string& originalString)
{
    std::string stringReverse;
    std::ranges::reverse_copy(originalString, std::back_inserter(stringReverse));
    return stringReverse;
}

inline std::vector<std::string> ReverseStrings(const std::vector<std::string>& originalStrings)
{
    std::vector<std::string> reversedStrings;
    reversedStrings.reserve(originalStrings.size());
    for (const auto& originalString : originalStrings)
    {
        reversedStrings.emplace_back(ReverseString(originalString));
    }
    return reversedStrings;
}