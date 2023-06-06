//
// Created by DripTooHard on 06-06-2023.
//

//
// Created by DripTooHard on 03-06-2023.
//

//
// Created by DripTooHard on 20-05-2023.
//


#include <Arduino.h>
#include "unity.h"
#include <RegexUtility.h>


/**
 * IMPORTANT: Remember not to use the same paths for the tests that need to be resat; They will overwrite each other.
 */

const char * TEST_STR = "ABCDEFG";
int SIZE_OF_TEST_STR = 7;

void setUp(void) {
    // set stuff up here
}


void tearDown(void) {
    // delete stuff down here
}

void endIDXGetsIDXAfterPattern(){
    TEST_ASSERT_EQUAL(2,RegexUtil::getEndIDX((unsigned char *) TEST_STR,SIZE_OF_TEST_STR,std::regex("AB")));
    TEST_ASSERT_EQUAL(5,RegexUtil::getEndIDX((unsigned char *) TEST_STR,SIZE_OF_TEST_STR,std::regex("DE")));
}

void startIDXGetsIDXAtStartOfPattern(){
    TEST_ASSERT_EQUAL(0,RegexUtil::getStartIDX((unsigned char *) TEST_STR,SIZE_OF_TEST_STR,std::regex("AB")));
    TEST_ASSERT_EQUAL(3,RegexUtil::getStartIDX((unsigned char *) TEST_STR,SIZE_OF_TEST_STR,std::regex("DE")));
}

void startIDXNoMatch(){
    TEST_ASSERT_EQUAL(-1,RegexUtil::getStartIDX((unsigned char *) TEST_STR,SIZE_OF_TEST_STR,std::regex("ACB")));
}

void endIDXNoMatch(){
    TEST_ASSERT_EQUAL(-1,RegexUtil::getEndIDX((unsigned char *) TEST_STR,SIZE_OF_TEST_STR,std::regex("ACB")));
}

void endIDXOutOfBounds(){
    try{
        RegexUtil::getEndIDX((unsigned char *) TEST_STR,SIZE_OF_TEST_STR,std::regex("DEFG"));
        TEST_FAIL_MESSAGE("REGEX UTIL DID NOT PASS AN ERROR WHEN THE INDEX AFTER THE PATTERN WAS OUT OF BOUNDS");
    }
    catch(std::invalid_argument ef){
    }
}

void setup()
{
    delay(5000); // service delay

    //DON'T PUT ANYTHING BEFORE THIS EXCEPT FOR DELAY!!!!
    UNITY_BEGIN(); //Define stuff after this
    RUN_TEST(endIDXGetsIDXAfterPattern);
    RUN_TEST(startIDXGetsIDXAtStartOfPattern);
    RUN_TEST(endIDXNoMatch);
    RUN_TEST(startIDXNoMatch);
    RUN_TEST(endIDXOutOfBounds);

    UNITY_END(); // stop unit testing
}

void loop()
{
}
