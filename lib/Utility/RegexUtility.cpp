//
// Created by DripTooHard on 05-06-2023.
//

#include "RegexUtility.h"


int RegexUtil::getEndIDX(const unsigned char *data, int size, std::regex formula) {
    int IDX = -1;

    std::string content(reinterpret_cast<const char*>(data), size);

    std::smatch match;
    if (std::regex_search(content, match, formula))
    {
        std::string matchString = match.str();
        IDX = match.position() + matchString.length();
    }

    //size_t is unsigned, whoopsie
    if(size<=IDX){
        log_e("INDEX OUT OF RANGE.\nINDEX: %i\nArray size: %i",IDX,size);
        throw std::invalid_argument("THE IDX AFTER THE END OF THE PATTERN IS OUT OF BOUNDS");
    }

    return IDX; //Returns -1 if the substring is not found

};


int RegexUtil::getStartIDX(const unsigned char *data, int size, std::regex formula) {
    std::string content(reinterpret_cast<const char*>(data), size);

    std::smatch match;
    if (std::regex_search(content, match, formula)) {
        std::string matchString = match.str();
        return match.position();
    }

    return -1;  // Return -1 if the substring is not found
};