#include "unity.h"
#include "../../lib/MVC/DataController.h"
#include <Arduino.h>

//first testing if there are no members in the model
void test_pressing_up_key_empty_table(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(UP_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
}

void test_pressing_down_key_empty_table(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(DOWN_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());

}

void test_pressing_left_key_empty_table(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(LEFT_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
}

void test_pressing_right_key_empty_table(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(RIGHT_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
}

//testing with 1-4 members, that is without scrolling
void test_pressing_up_key_non_full_table(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    char name1[] = "Bjarke";
    char name2[] = "Benny";
    Member mem1 = Member(name1,NavigationData());
    Member mem2 = Member(name2,NavigationData());
    dataController.addGroupMember(mem1);
    dataController.addGroupMember(mem2);
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(UP_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    //test if not at the top already
    dataController.setTableIndex(2);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(2,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(UP_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
}

void test_pressing_down_key_non_full_table(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    char name1[] = "Bjarke";
    char name2[] = "Benny";
    Member mem1 = Member(name1,NavigationData());
    Member mem2 = Member(name2,NavigationData());
    dataController.addGroupMember(mem1);
    dataController.addGroupMember(mem2);
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(DOWN_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(2,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    //test if at the bottom
    dataController.handleUserInput(DOWN_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(2,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
}

void test_pressing_left_key_non_full_table(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    char name1[] = "Bjarke";
    char name2[] = "Benny";
    Member mem1 = Member(name1,NavigationData());
    Member mem2 = Member(name2,NavigationData());
    dataController.addGroupMember(mem1);
    dataController.addGroupMember(mem2);
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(LEFT_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(1,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(LEFT_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
}

void test_pressing_right_key_non_full_table(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    char name1[] = "Bjarke";
    char name2[] = "Benny";
    Member mem1 = Member(name1,NavigationData());
    Member mem2 = Member(name2,NavigationData());
    dataController.addGroupMember(mem1);
    dataController.addGroupMember(mem2);
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(RIGHT_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(1,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    //test if at the bottom
    dataController.handleUserInput(RIGHT_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
}

//Testing with more than 4 members to check scrolling and changing of indexes
void test_pressing_up_key_full_table(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    /*char name1[] = "Bjarke";
    char name2[] = "Benny";
    Member mem1 = Member(name1,NavigationData());
    Member mem2 = Member(name2,NavigationData());
    dataController.addGroupMember(mem1);
    dataController.addGroupMember(mem2);*/
    char names[5][8] = {"Bjarke", "Benny", "Birger", "Bjarne", "Bent"};
    for(int i = 0; i < 5; i++){
        Member m = Member(names[i],NavigationData());
        dataController.addGroupMember(m);
    }
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(UP_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    //test if topTableIndex > 0 so the table can scroll up
    dataController.setTableIndex(0);
    dataController.setTopTableIndex(1);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(1,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(UP_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
}

void test_pressing_down_key_full_table(void) {

}

void test_pressing_left_key_full_table(void) {

}

void test_pressing_right_key_full_table(void) {

}

void test_pressing_back_key_no_change_of_index_table_state(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(BACK_KEY,&dev);
    TEST_ASSERT_EQUAL(START_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
}

void test_pressing_back_key_change_of_index_table_state(void) {//testing if index when changed down or left is reset after
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    char name1[] = "Bjarke";
    char name2[] = "Benny";
    Member mem1 = Member(name1,NavigationData());
    Member mem2 = Member(name2,NavigationData());
    dataController.addGroupMember(mem1);
    dataController.addGroupMember(mem2);
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(RIGHT_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(1,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(DOWN_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(3,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
    dataController.handleUserInput(BACK_KEY,&dev);
    TEST_ASSERT_EQUAL(START_STATE,dataController.getModelState());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTableIndex());
    TEST_ASSERT_EQUAL(0,dataController.getModel().getTopTableIndex());
}

void test_pressing_enter_key_table_state(void) {
    DataView dataView = DataView();
    DataController dataController = DataController(dataView);
    SSD1306_t dev;
    dataController.handleUserInput(DOWN_KEY,&dev);
    //start of test
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
    dataController.handleUserInput(ENTER_KEY,&dev);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataController.getModelState());
}

void runTableStateTests(void) {
    RUN_TEST(test_pressing_enter_key_table_state);
    RUN_TEST(test_pressing_up_key_empty_table);
    RUN_TEST(test_pressing_up_key_non_full_table);
    delay(10000);
    RUN_TEST(test_pressing_up_key_full_table);
    delay(10000);
    RUN_TEST(test_pressing_down_key_empty_table);
    RUN_TEST(test_pressing_down_key_non_full_table);
    delay(2000);
    RUN_TEST(test_pressing_down_key_full_table);
    RUN_TEST(test_pressing_left_key_empty_table);
    RUN_TEST(test_pressing_left_key_non_full_table);
    delay(2000);
    RUN_TEST(test_pressing_left_key_full_table);
    RUN_TEST(test_pressing_right_key_empty_table);
    RUN_TEST(test_pressing_right_key_non_full_table);
    delay(2000);
    RUN_TEST(test_pressing_right_key_full_table);
    RUN_TEST(test_pressing_back_key_no_change_of_index_table_state);
    RUN_TEST(test_pressing_back_key_change_of_index_table_state);
}