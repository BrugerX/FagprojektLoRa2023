#include "unity.h"
#include "../../lib/MVC/DataModel.h"
#include <Arduino.h>

//This test is testing the following methods:
//    addGroupMember(Member groupMember);
//    removeGroupMember(char index);
//    removeGroupMember(Member groupMember);
//    getNumberOfMembers();
#ifndef TEST_ADDING_AND_DELETION_OF_MEMBERS_HPP
#define TEST_ADDING_AND_DELETION_OF_MEMBERS_HPP
DataView dataViewet = DataView();
DataModel model = DataModel(0, &dataViewet);
char ID2[] = "AddTwo";
Member m2 = Member(ID2,NavigationData());

void test_adding_members(void) {
    int startingNumberOfMembers = model.getNumberOfMembers();
    TEST_ASSERT_EQUAL(0, startingNumberOfMembers);
    char ID[] = "AddOne";
    Member m = Member(ID,NavigationData());
    model.addGroupMember(m);
    TEST_ASSERT_EQUAL(1, model.getNumberOfMembers());

    model.addGroupMember(m2);
    TEST_ASSERT_EQUAL(2, model.getNumberOfMembers());
}

void test_deleting_members(void) {
    model.removeGroupMember(0);
    TEST_ASSERT_EQUAL(1, model.getNumberOfMembers());
    int result = strcmp(ID2, model.getMemberID(0));
    TEST_ASSERT_EQUAL(0,result);
    model.removeGroupMember(m2);
    TEST_ASSERT_EQUAL(0, model.getNumberOfMembers());
}

void test_adding_to_many_members(void) {
    char error[] = "You have to many members, remove some first if you want to add more";
    bool result;
    char ID[] = "ID";
    Member m = Member(ID, NavigationData());
    for(int i = 0; i < MAX_NUMBER_OF_MEMBERS; i++){
        model.addGroupMember(m);
    }
    TEST_ASSERT_EQUAL(MAX_NUMBER_OF_MEMBERS,model.getNumberOfMembers());
    try {model.addGroupMember(m);}
    catch (const exception& e){
        result = strcmp(error, e.what()) == 0;
    }
    TEST_ASSERT_EQUAL(1,result);
    TEST_ASSERT_EQUAL(MAX_NUMBER_OF_MEMBERS,model.getNumberOfMembers()); //we can not have more than 127 members
}

//test for adding members with long names


void runTestsAddAndDelOfMembers(void) {
    RUN_TEST(test_adding_members);
    RUN_TEST(test_deleting_members);
    RUN_TEST(test_adding_to_many_members);
}

#endif
