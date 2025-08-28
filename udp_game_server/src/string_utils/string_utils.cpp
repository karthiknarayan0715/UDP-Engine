#include "models/constants/constants.h"
#include "string_utils/string_utils.h"

#include <vector>

std::vector<std::string> split(std::string str, std::string delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));

    return result;
}