//
// Created by DripTooHard on 05-06-2023.
//

#ifndef FAGPROJEKTLORA2023_REGEXUTILITY_H
#define FAGPROJEKTLORA2023_REGEXUTILITY_H

#include <Arduino.h>
#include <regex>

class RegexUtil{
public:
    static int getEndIDX (const unsigned char *data, size_t size, std::regex formula);
    static int getStartIDX(const unsigned char *data, size_t size, std::regex formula);
};

#endif //FAGPROJEKTLORA2023_REGEXUTILITY_H
