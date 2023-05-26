//
// Created by DripTooHard on 20-05-2023.
//

#include <Arduino.h>
#include <unity.h>
#include "../../lib/Utility/Utility.cpp"
#include <FileManager.cpp>
#include "esp_system.h"

const char * TEST_STR_PATH;
char * TEST_STR;
SPIFFSFileManager * spiffy;
int testInt;

bool didWeRestart(){
    return  esp_reset_reason() == ESP_RST_SW;
}

void setUp(void) {
    // set stuff up here
    TEST_STR_PATH = "/abc";
    TEST_STR = "ABC";
}


void tearDown(void) {
    // delete stuff down here
    testInt = 3;
}


/**
* Scenarie:
 * ABCDEF eksisterer ikke, vi gemmer det og genstarter ESP'en
 * ABCDEF eksisterer nu, vi kan loade det
 * Vi sletter ABCDEF, det eksisterer ikke
*
 */

void dataIsSavedAfterReboot(){
    //Before the reset we save it, and assert that we have indeed saved it
    if(!didWeRestart()){
        TEST_ASSERT_FALSE(spiffy->exists(TEST_STR_PATH));
        spiffy->save_file(TEST_STR_PATH,(const unsigned char *) TEST_STR);
        TEST_ASSERT_TRUE(spiffy->exists(TEST_STR_PATH));
    }
        //After the reset we check to see if it still exists, if we can load it, we then delete it
    else{
        TEST_ASSERT_TRUE(spiffy->exists(TEST_STR_PATH));
        unsigned char * load_result_arr;
        spiffy->load_file(TEST_STR_PATH,load_result_arr);

        //Time to delete it
        TEST_ASSERT_EQUAL_STRING(TEST_STR,load_result_arr);
        spiffy->delete_file(TEST_STR_PATH);
        TEST_ASSERT_FALSE(spiffy->exists(TEST_STR_PATH));
    }
}

/**
* Scenarie: Vi gemmer noget, det eksisterer, vi sletter det, det eksisterer ikke
*
 */


/**
* Scenarie: Vi gemmer ABCDEF, vi loader det i et array og får ABCDEF
*
 */

/**
* Scenarie: Vi gemmer ABCDEF, genstarter ESP32'eren, og vi kan loade det og det eksisterer,
*
 */

/**
* Scenarie: Vi laver to SPIFFS objekter på samme tid
 * Der eksisterer Spiffs objekt 1, der eksisterer spiffs objekt 2, vi bruger spiffs objekt 1 til at gemme ABCDF, vi bruger spiffs objekt 2 til at loade ABCDF
 * ABCDF er nu i arrayet, som vi har brugt til at loade
 * Vi genstarter ESP32'eren
 * Vi laver et Spiffs objekt 3, vi loader ABCDF, ABCDF er nu i arrayet
*/

/**
* Scenarie: Vi laver, sletter, laver
 * Givet laver spiffs2
 * Og sletter spiffs2
 * Og laver spiffs 1
 * Så bør spiffs1 være mounted
*/

/**
* Scenarie: Vi laver, vi laver, vi sletter
 * Givet laver spiffs2
 * Og laver spiffs 1
 * Og sletter spiffs 2
 * Og vi prøver at gemme "ABCDF" i path "EKG"
 * Så bør vi kunne loade "EKG" vhja. Spiffs1
*/

void setup()
{
    delay(5000); // service delay

    //DON'T PUT ANYTHING BEFORE THIS EXCEPT FOR DELAY!!!!
    UNITY_BEGIN(); //Define stuff after this
    RUN_TEST(dataIsSavedAfterReboot);
    if(!didWeRestart()){
        esp_restart();
    }
    UNITY_END(); // stop unit testing
}

void loop()
{
}