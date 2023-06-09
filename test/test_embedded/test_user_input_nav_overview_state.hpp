#include "unity.h"
#include "../../lib/MVC/DataController.h"
#include <Arduino.h>

#ifndef FAGPROJEKTLORA2023_TEST_USER_INPUT_NAV_OVERVIEW_STATE_H
#define FAGPROJEKTLORA2023_TEST_USER_INPUT_NAV_OVERVIEW_STATE_H

DataView dataViewNS = DataView();
DataController dataControllerNS = DataController(&dataViewNS);
SSD1306_t devNS;
char namesNS[5][8] = {"Bjarke", "Benny", "Birger", "Bjarne", "Bent"};

void test_pressing_other_keys_nav_state(void) {
    dataControllerNS.setState(NAV_OVERVIEW_STATE);
    for(int i = 0; i < 5; i++){
        Member m = Member(namesNS[i],NavigationData());
        dataControllerNS.addGroupMember(m);
    }
    //start of test
    TEST_ASSERT_EQUAL(NAV_OVERVIEW_STATE,dataControllerNS.getModelState());
    dataControllerTS.handleUserInput(UP_KEY,&devNS);
    TEST_ASSERT_EQUAL(NAV_OVERVIEW_STATE,dataControllerNS.getModelState());
    dataControllerTS.handleUserInput(DOWN_KEY,&devNS);
    TEST_ASSERT_EQUAL(NAV_OVERVIEW_STATE,dataControllerNS.getModelState());
    dataControllerTS.handleUserInput(LEFT_KEY,&devNS);
    TEST_ASSERT_EQUAL(NAV_OVERVIEW_STATE,dataControllerNS.getModelState());
    dataControllerTS.handleUserInput(RIGHT_KEY,&devNS);
}

void test_pressing_back_key_with_changed_index_nav_state(void){
    dataControllerNS.setState(NAV_OVERVIEW_STATE);
    char ti = 3; //arbitrary test tableIndex within range of our number of members (6)
    char tti = 1; //arbitrary test topTableIndex within range of our number of members (6)
    dataControllerNS.setTableIndex(ti);
    dataControllerNS.setTopTableIndex(tti);
    //start of test
    TEST_ASSERT_EQUAL(NAV_OVERVIEW_STATE,dataControllerNS.getModelState());
    TEST_ASSERT_EQUAL(ti,dataControllerNS.getTableIndex());
    TEST_ASSERT_EQUAL(tti,dataControllerNS.getModel().getTopTableIndex());
    dataControllerNS.handleUserInput(BACK_KEY,&devNS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerNS.getModelState());
    TEST_ASSERT_EQUAL(ti,dataControllerNS.getTableIndex());
    TEST_ASSERT_EQUAL(tti,dataControllerNS.getModel().getTopTableIndex());
}

void test_pressing_back_key_with_same_index_nav_state(void){
    TEST_ASSERT_EQUAL(NAV_OVERVIEW_STATE,dataControllerNS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerNS.getTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerNS.getModel().getTopTableIndex());
    dataControllerNS.handleUserInput(BACK_KEY,&devNS);
    TEST_ASSERT_EQUAL(TABLE_STATE,dataControllerNS.getModelState());
    TEST_ASSERT_EQUAL(0,dataControllerNS.getModel().getTopTableIndex());
    TEST_ASSERT_EQUAL(0,dataControllerNS.getTableIndex());
}

void test_pressing_enter_key_nav_state(void){
    TEST_ASSERT_EQUAL(NAV_OVERVIEW_STATE,dataControllerNS.getModelState());
    TEST_ASSERT(!dataControllerNS.getModel().getMemberHighlight()); //it should be false
    dataControllerNS.handleUserInput(ENTER_KEY, &devNS);
    TEST_ASSERT_EQUAL(NAV_OVERVIEW_STATE,dataControllerNS.getModelState());
    TEST_ASSERT(dataControllerNS.getModel().getMemberHighlight());
    dataControllerNS.handleUserInput(ENTER_KEY, &devNS); //pressing again makes it false again
    TEST_ASSERT_EQUAL(NAV_OVERVIEW_STATE,dataControllerNS.getModelState());
    TEST_ASSERT(!dataControllerNS.getModel().getMemberHighlight()); //it should be false
}

//test to check that highlight will be the same for both indexes

void runNavOverviewStateTests(void) {
    RUN_TEST(test_pressing_other_keys_nav_state);
    RUN_TEST(test_pressing_enter_key_nav_state);
    RUN_TEST(test_pressing_back_key_with_same_index_nav_state);
    RUN_TEST(test_pressing_back_key_with_changed_index_nav_state);
}

#endif //FAGPROJEKTLORA2023_TEST_USER_INPUT_NAV_OVERVIEW_STATE_H
