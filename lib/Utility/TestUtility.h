//
// Created by DripTooHard on 29-05-2023.
//
//*
//* Contains methods for easier unit testing
//*

#include "stddef.h"

#ifndef FAGPROJEKTLORA2023_TESTUTILITY_H
#define FAGPROJEKTLORA2023_TESTUTILITY_H

//The coolest macro in the world? Probably.
#define TEST_ASSERT_NOT_EQUAL_STRING(str1, str2) TEST_ASSERT_TRUE_MESSAGE(assertNotEqualArrayString(str1, str2),#str1 " AND " #str2 " ARE NOT UNEQUAL")

//Asserts that the two arrays contain at least one element, that differentiates the two
bool assertNotEqualArray(unsigned char * arr1, unsigned char * arr2, size_t nrElements);


//Asserts that the two string arrays contain at least one element, that differentiates the two between the 0th index and their first \0
bool assertNotEqualArrayString(unsigned char * arr1, unsigned char * arr2);

#endif //FAGPROJEKTLORA2023_TESTUTILITY_H
