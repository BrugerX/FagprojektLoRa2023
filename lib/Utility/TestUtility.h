//
// Created by DripTooHard on 29-05-2023.
//

#include "stddef.h"

#ifndef FAGPROJEKTLORA2023_TESTUTILITY_H
#define FAGPROJEKTLORA2023_TESTUTILITY_H

//The coolest macro in the world? Probably.
#define TEST_ASSERT_NOT_EQUAL_STRING(str1, str2) TEST_ASSERT_TRUE_MESSAGE(assertNotEqualArrayString(str1, str2),#str1 " AND " #str2 " ARE EQUAL")

bool assertNotEqualArray(unsigned char * arr1, unsigned char * arr2, size_t nrElements);
bool assertNotEqualArrayString(unsigned char * arr1, unsigned char * arr2);

#endif //FAGPROJEKTLORA2023_TESTUTILITY_H
