#include "unity.h"
#include "../../lib/MVC/DataController.h"
#include <Arduino.h>

DataView dataViewCS = DataView();
DataController dataControllerCS = DataController(&dataViewCS);

void test_pressing_back_key_compass_state(void) {
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataControllerCS.getModelState());
    dataControllerCS.handleUserInput(BACK_KEY);
    TEST_ASSERT_EQUAL(START_STATE,dataControllerCS.getModelState());
}

void test_pressing_other_keys_compass_state(void) {
    dataControllerCS.setState(COMPASS_STATE);
    //start of test
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataControllerCS.getModelState());
    dataControllerCS.handleUserInput(LEFT_KEY);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataControllerCS.getModelState());
    dataControllerCS.handleUserInput(RIGHT_KEY);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataControllerCS.getModelState());
    dataControllerCS.handleUserInput(UP_KEY);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataControllerCS.getModelState());
    dataControllerCS.handleUserInput(DOWN_KEY);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataControllerCS.getModelState());
    dataControllerCS.handleUserInput(ENTER_KEY);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataControllerCS.getModelState());
}

void runCompassStateTests(void) {
    RUN_TEST(test_pressing_other_keys_compass_state);
    RUN_TEST(test_pressing_back_key_compass_state);
}
