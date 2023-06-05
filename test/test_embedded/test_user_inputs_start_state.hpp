#include "unity.h"
#include "../../lib/MVC/DataController.h"
#include <Arduino.h>

//testing that the different user inputs when in the "start state" are following the desired behavior

void test_pressing_up_key(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    //start of test
    TEST_ASSERT_EQUAL(START_STATE,dataController.getModelState());
    dataController.handleUserInput(UP_KEY,&dev);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataController.getModelState());
}

void test_pressing_down_key(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    //start of test
    TEST_ASSERT_EQUAL(START_STATE,dataController.getModelState());
    dataController.handleUserInput(DOWN_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
}

void test_pressing_other_keys(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    //start of test
    TEST_ASSERT_EQUAL(START_STATE,dataController.getModelState());
    dataController.handleUserInput(LEFT_KEY,&dev);
    TEST_ASSERT_EQUAL(START_STATE,dataController.getModelState());
    dataController.handleUserInput(RIGHT_KEY,&dev);
    TEST_ASSERT_EQUAL(START_STATE,dataController.getModelState());
    dataController.handleUserInput(BACK_KEY,&dev);
    TEST_ASSERT_EQUAL(START_STATE,dataController.getModelState());
    dataController.handleUserInput(ENTER_KEY,&dev);
    TEST_ASSERT_EQUAL(START_STATE,dataController.getModelState());
}

void runStartStateTests(void) {
    RUN_TEST(test_pressing_other_keys);
    RUN_TEST(test_pressing_up_key);
    RUN_TEST(test_pressing_down_key);
}
