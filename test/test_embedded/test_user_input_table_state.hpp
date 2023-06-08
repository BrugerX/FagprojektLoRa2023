#include "unity.h"
#include "../../lib/MVC/DataController.h"
#include <Arduino.h>

DataView dataViewTS = DataView();
DataController dataControllerTS = DataController(dataViewTS);
SSD1306_t devTS;
char names[5][8] = {"Bjarke", "Benny", "Birger", "Bjarne", "Bent"};


//first testing if there are no members in the model
void test_pressing_up_key_empty_table(void) {
    dataControllerTS.setState(TABLE_STATE);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(UP_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
}

void test_pressing_down_key_empty_table(void) {
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(DOWN_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());

}

void test_pressing_left_key_empty_table(void) {
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(LEFT_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
}

void test_pressing_right_key_empty_table(void) {
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(RIGHT_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
}

//testing with 1-4 members, that is without scrolling
void test_pressing_up_key_non_full_table(void) {
    Member mem1 = Member(names[0],NavigationData());
    Member mem2 = Member(names[1],NavigationData());
    dataControllerTS.addGroupMember(mem1);
    dataControllerTS.addGroupMember(mem2);
    dataControllerTS.setState(TABLE_STATE);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(UP_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    //test if not at the top already
    dataControllerTS.setTableIndex(2);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(2,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(UP_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
}

void test_pressing_down_key_non_full_table(void) {
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(DOWN_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(2,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    //test if at the bottom
    dataControllerTS.handleUserInput(DOWN_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(2,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
}

void test_pressing_left_key_non_full_table(void) {
    dataControllerTS.setTableIndex(0);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(LEFT_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(1,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(LEFT_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
}

void test_pressing_right_key_non_full_table(void) {
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(RIGHT_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(1,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(RIGHT_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
}

//Testing with more than 4 members to check scrolling and changing of indexes
void test_pressing_up_key_full_table(void) {
    dataControllerTS.setState(TABLE_STATE);
    for(int i = 2; i < 5; i++){
        Member m = Member(names[i],NavigationData());
        dataControllerTS.addGroupMember(m);
    }
    //start of test when it is not possible to scroll up
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(UP_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    //test if topTableIndex > 0 so the table can scroll up
    dataControllerTS.setTableIndex(0);
    dataControllerTS.setTopTableIndex(1);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(1,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(UP_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
}

void test_pressing_down_key_full_table(void) {
    dataControllerTS.setTableIndex(6);
    //start of test when possible to scroll down
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(6,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(DOWN_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(8,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(1,dataControllerTS.getModel().getTopTableIndex());
    //test if at bottom so the table can not scroll down
    dataControllerTS.handleUserInput(DOWN_KEY,&devTS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(8,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(1,dataControllerTS.getModel().getTopTableIndex());
}

void test_pressing_back_key_no_change_of_index_table_state(void) {
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.handleUserInput(BACK_KEY,&devTS);
    TEST_ASSERT_EQUAL(START_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
}

void test_pressing_back_key_change_of_index_table_state(void) {//testing if index when changed down or left is reset after
    dataControllerTS.setState(TABLE_STATE);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
    dataControllerTS.setTableIndex(3); //changing to non-zero number
    dataControllerTS.setTopTableIndex(1); // changing to non-zero number
    dataControllerTS.handleUserInput(BACK_KEY,&devTS);
    TEST_ASSERT_EQUAL(START_STATE,dataControllerTS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerTS.getModel().getTopTableIndex());
}

void test_pressing_enter_key_table_state(void) {
    dataControllerTS.setState(TABLE_STATE);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerTS.getModelState());
    dataControllerTS.handleUserInput(ENTER_KEY,&devTS);
    TEST_ASSERT_EQUAL(NAV_OVERVIEW_STATE,dataControllerTS.getModelState());
}
//maybe test that indexes are kept when pressing enter.

void runTableStateTests(void) {
    RUN_TEST(test_pressing_up_key_empty_table);
    RUN_TEST(test_pressing_down_key_empty_table);
    RUN_TEST(test_pressing_left_key_empty_table);
    RUN_TEST(test_pressing_right_key_empty_table);
    RUN_TEST(test_pressing_back_key_no_change_of_index_table_state);
    RUN_TEST(test_pressing_up_key_non_full_table);
    RUN_TEST(test_pressing_down_key_non_full_table);
    RUN_TEST(test_pressing_left_key_non_full_table);
    RUN_TEST(test_pressing_right_key_non_full_table);
    RUN_TEST(test_pressing_enter_key_table_state);
    RUN_TEST(test_pressing_back_key_change_of_index_table_state);
    RUN_TEST(test_pressing_up_key_full_table);
    RUN_TEST(test_pressing_down_key_full_table);
}