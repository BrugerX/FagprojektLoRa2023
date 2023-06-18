//
// Created by DripTooHard on 05-06-2023.
//
//*
//* Contains methods related to simple ReGex operations
//*

#ifndef FAGPROJEKTLORA2023_REGEXUTILITY_H
#define FAGPROJEKTLORA2023_REGEXUTILITY_H

#include <Arduino.h>
#include <regex>

class RegexUtil{
public:
    /**
     * @data The unsigned char array we need to search through
     * @size The size of this string in number of indices
     * @formula The regex formula we will match
     *
     * @return
     *        Returns the index immediately after the end of the match
     *        Else it returns -1
     */
    static int getEndIDX (const unsigned char *data, int size, std::regex formula);

    /**
     * @data The string we need to search through
     * @size The size of this string in number of indices
     * @formula The regex formula we will match
     *
     * @return
     *        Returns the index at the start of the match
     *        Else it returns -1
     */

    static int getStartIDX(const unsigned char *data, int size, std::regex formula);
};

#endif //FAGPROJEKTLORA2023_REGEXUTILITY_H
