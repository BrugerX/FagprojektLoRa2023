#include "unity.h"
#include "../../lib/MVC/DataController.h"
#include <Arduino.h>

//testing that the different user inputs when in the "start state" are following the desired behavior

DataView dataViewSS = DataView();
DataController dataControllerSS = DataController(&dataViewSS);

void test_pressing_up_key_start_state(void) {
    dataControllerSS.setState(START_STATE);
    //start of test
    TEST_ASSERT_EQUAL(START_STATE,dataControllerSS.getModelState());
    dataControllerSS.handleUserInput(UP_KEY);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataControllerSS.getModelState());
}

void test_pressing_down_key_start_state(void) {
    dataControllerSS.setState(START_STATE);
    //start of test
    TEST_ASSERT_EQUAL(START_STATE,dataControllerSS.getModelState());
    dataControllerSS.handleUserInput(DOWN_KEY);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerSS.getModelState());
}

void test_pressing_other_keys_start_state(void) {
    //start of test
    TEST_ASSERT_EQUAL(START_STATE,dataControllerSS.getModelState());
    dataControllerSS.handleUserInput(LEFT_KEY);
    TEST_ASSERT_EQUAL(START_STATE,dataControllerSS.getModelState());
    dataControllerSS.handleUserInput(RIGHT_KEY);
    TEST_ASSERT_EQUAL(START_STATE,dataControllerSS.getModelState());
    dataControllerSS.handleUserInput(BACK_KEY);
    TEST_ASSERT_EQUAL(START_STATE,dataControllerSS.getModelState());
    dataControllerSS.handleUserInput(ENTER_KEY);
    TEST_ASSERT_EQUAL(START_STATE,dataControllerSS.getModelState());
}

void runStartStateTests(void) {
    RUN_TEST(test_pressing_other_keys_start_state);
    RUN_TEST(test_pressing_up_key_start_state);
    RUN_TEST(test_pressing_down_key_start_state);
}
