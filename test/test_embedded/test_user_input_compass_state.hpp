#include "unity.h"
#include "../../lib/MVC/DataController.h"
#include <Arduino.h>

void test_pressing_back_key_compass_state(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    dataController.handleUserInput(UP_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataController.getModelState());
    dataController.handleUserInput(BACK_KEY,&dev);
    TEST_ASSERT_EQUAL(START_STATE,dataController.getModelState());
}

void test_pressing_other_keys_compass_state(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    dataController.handleUserInput(UP_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataController.getModelState());
    dataController.handleUserInput(LEFT_KEY,&dev);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataController.getModelState());
    dataController.handleUserInput(RIGHT_KEY,&dev);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataController.getModelState());
    dataController.handleUserInput(UP_KEY,&dev);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataController.getModelState());
    dataController.handleUserInput(DOWN_KEY,&dev);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataController.getModelState());
    dataController.handleUserInput(ENTER_KEY,&dev);
    TEST_ASSERT_EQUAL(COMPASS_STATE,dataController.getModelState());
}

void runCompassStateTests(void) {
    RUN_TEST(test_pressing_other_keys_compass_state);
    RUN_TEST(test_pressing_back_key_compass_state);
}
