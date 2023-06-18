//
// Created by DripTooHard on 03-04-2023.
//
#include "Arduino.h"

/*
 *
 * Contains methods that make it easier to develop,test and debug the software,
 * but which add no functionality to the software.
 *
 */

#ifndef UNTITLED1_UTILITY_H
#define UNTITLED1_UTILITY_H

//Prints an unsigned char array into either numerical or text format based on the base
void println_unsignedString(unsigned char * unsginedString,int strlen, int base);

void println_unsignedString(unsigned char * unsginedString, int base);

void println_unsignedString(const unsigned char * unsginedString,int strlen, int base);

void fill_alphanumeric_unsignedString(unsigned char * unsignedString, size_t sizeOf);

void fill_char_unsignedString(unsigned char * unsignedString, size_t sizeOf,unsigned char chosenChar);

void get_size(unsigned char * unsignedString, size_t * toPutSize);

void get_size(unsigned char * unsignedString, int * toPutSize);

#endif //UNTITLED1_UTILITY_H
