//
// Created by DripTooHard on 03-04-2023.
//
#include "Arduino.h"

/*
 *
 * Contains methods that make it easier to develop and debug unsigned strings
 *
 */

#ifndef UNTITLED1_UTILITY_H
#define UNTITLED1_UTILITY_H

//Prints an unsigned char array into either numerical or text format based on the base
void println_unsignedString(unsigned char * unsginedString,int strlen, int base);

void println_unsignedString(unsigned char * unsginedString, int base);

void println_unsignedString(const unsigned char * unsginedString,int strlen, int base);


//Generates the following array ReGex [A,B,C,...,z]^(|[A,B,C,...,z]|%(sizeOf))
void fill_alphanumeric_unsignedString(unsigned char * unsignedString, size_t sizeOf);

//Fills the unsigned string array with a single char
void fill_char_unsignedString(unsigned char * unsignedString, size_t sizeOf,unsigned char chosenChar);

//Gets the size of the unsigned string array and puts it in toPutSize
void get_size(unsigned char * unsignedString, size_t * toPutSize);

void get_size(unsigned char * unsignedString, int * toPutSize);

#endif //UNTITLED1_UTILITY_H
