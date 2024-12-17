#pragma once

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> LineIntoWords(const std::string& sentence)
{
    std::istringstream iss(sentence);
    return std::vector<std::string>(
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>{});
}
