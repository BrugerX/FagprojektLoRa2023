#include "unity.h"
#include "../../lib/MVC/DataController.h"
#include <Arduino.h>

DataView dataView = DataView();
DataController dataController = DataController(dataView);
char ID2[] = "AddTwo";
Member m2 = Member(ID2,NavigationData());

void setUp(void) {
}

void tearDown(void) {
    // clean stuff up here
}

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


int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_adding_members);
    RUN_TEST(test_deleting_members);
    return UNITY_END();
}

void setup() {
    delay(2000);

    runUnityTests();
}
void loop() {}