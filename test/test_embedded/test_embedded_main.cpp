#include "unity.h"
#include <Arduino.h>

#include "test_adding_and_deletion_of_members.hpp"
#include "test_user_inputs_start_state.hpp"
#include "test_user_input_compass_state.hpp"
#include "test_user_input_table_state.hpp"

void setUp(void) {
}

void tearDown(void) {
    // clean stuff up here
}

void setup() {
    delay(2000);

    UNITY_BEGIN();
    runTestsAddAndDelOfMembers();
    runStartStateTests();
    runCompassStateTests();
    //runTableStateTests();
    UNITY_END();
}
void loop() {}
