//
// Created by DripTooHard on 05-06-2023.
//

#include "RegexUtility.h"

/**
 * @data The string we need to search through
 * @size The size of this string in number of indices
 * @formula The regex formula we will match
 *
 * @return
 *        Returns the index immediately after the end of the match
 *        Else it returns -1
 */
int RegexUtil::getEndIDX(const unsigned char *data, size_t size, std::regex formula) {
    std::string content(reinterpret_cast<const char*>(data), size);

    std::smatch match;
    if (std::regex_search(content, match, formula)) {
        std::string matchString = match.str();
        return match.position() + matchString.length();
    }

    return -1;  // Return -1 if the substring is not found
};

/**
 * @data The string we need to search through
 * @size The size of this string in number of indices
 * @formula The regex formula we will match
 *
 * @return
 *        Returns the index at the start of the match
 *        Else it returns -1
 */

int RegexUtil::getStartIDX(const unsigned char *data, size_t size, std::regex formula) {
    std::string content(reinterpret_cast<const char*>(data), size);

    std::smatch match;
    if (std::regex_search(content, match, formula)) {
        std::string matchString = match.str();
        return match.position();
    }

    return -1;  // Return -1 if the substring is not found
};