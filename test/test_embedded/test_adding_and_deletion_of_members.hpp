#include "unity.h"
#include "../../lib/MVC/DataController.h"
#include <Arduino.h>

//This test is testing the following methods:
//    addGroupMember(Member groupMember);
//    removeGroupMember(char index);
//    removeGroupMember(Member groupMember);
//    getNumberOfMembers();

DataView dataView = DataView();
DataController dataController = DataController(dataView);
char ID2[] = "AddTwo";
Member m2 = Member(ID2,NavigationData());

void test_adding_members(void) {
    int startingNumberOfMembers = dataController.getModel().getNumberOfMembers();
    TEST_ASSERT_EQUAL(0, startingNumberOfMembers);
    char ID[] = "AddOne";
    Member m = Member(ID,NavigationData());
    dataController.addGroupMember(m);
    TEST_ASSERT_EQUAL(1,dataController.getModel().getNumberOfMembers());

    dataController.addGroupMember(m2);
    TEST_ASSERT_EQUAL(2,dataController.getModel().getNumberOfMembers());
}

void test_deleting_members(void) {
    dataController.removeGroupMember(0);
    TEST_ASSERT_EQUAL(1,dataController.getModel().getNumberOfMembers());
    int result = strcmp(ID2,dataController.getModel().getMemberID(0));
    TEST_ASSERT_EQUAL(0,result);
    dataController.removeGroupMember(m2);
    TEST_ASSERT_EQUAL(0, dataController.getModel().getNumberOfMembers());
}

void test_adding_to_many_members(void) {
    char error[] = "You have to many members, remove some first if you want to add more";
    bool result;
    DataView view = DataView();
    DataController controller = DataController(view);
    char ID[] = "ID";
    Member m = Member(ID, NavigationData());
    for(int i = 0; i < MAX_NUMBER_OF_MEMBERS; i++){
        controller.addGroupMember(m);
    }
    TEST_ASSERT_EQUAL(MAX_NUMBER_OF_MEMBERS,controller.getModel().getNumberOfMembers());
    try {controller.addGroupMember(m);}
    catch (const exception& e){
        result = strcmp(error, e.what()) == 0;
    }
    TEST_ASSERT_EQUAL(1,result);
    TEST_ASSERT_EQUAL(MAX_NUMBER_OF_MEMBERS,controller.getModel().getNumberOfMembers()); //we can not have more than 255 members
}


void runTestsAddAndDelOfMembers(void) {
    //UNITY_BEGIN();
    RUN_TEST(test_adding_members);
    RUN_TEST(test_deleting_members);
    RUN_TEST(test_adding_to_many_members);
    //return UNITY_END();
}
