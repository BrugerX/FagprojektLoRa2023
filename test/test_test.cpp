#include <Arduino.h>
#include <unity.h>

//
// Created by DripTooHard on 14-05-2023.
//



String STR_TO_TEST;

void setUp(void) {
    // set stuff up here
    STR_TO_TEST = "Hello, world!";
}


void tearDown(void){
    STR_TO_TEST = "";
}

void len_is_greater_than_two(){
    TEST_ASSERT_GREATER_OR_EQUAL(3,sizeof(STR_TO_TEST));
}

void string_remains_after_teardown(){
    String testString = "Hello, world!";
    TEST_ASSERT_EQUAL_STRING("Hello, world!",STR_TO_TEST.c_str());
}

void setup()
{
    delay(2000); // service delay
    UNITY_BEGIN();

    RUN_TEST(len_is_greater_than_two);
    RUN_TEST(string_remains_after_teardown);

    UNITY_END(); // stop unit testing
}

void loop()
{
}