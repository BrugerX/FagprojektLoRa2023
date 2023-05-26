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

}

void fakeTest(){
    TEST_ASSERT_EQUAL_MESSAGE(true,true,(char *) didWeRestart());
    TEST_ASSERT_TRUE(true);
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
        if(!spiffy->exists(TEST_STR_PATH)){
        spiffy->save_file(TEST_STR_PATH,(const unsigned char *) TEST_STR);}
        TEST_ASSERT_TRUE(spiffy->exists(TEST_STR_PATH));
    }
    //After the reset we check to see if it still exists, if we can load it, we then delete it
    else{
        TEST_ASSERT_TRUE(spiffy->exists(TEST_STR_PATH));
        unsigned char load_result_arr[sizeof(TEST_STR)-1];
        spiffy->load_file(TEST_STR_PATH,load_result_arr);

        //Time to delete it
        TEST_ASSERT_EQUAL_STRING(TEST_STR,load_result_arr);
        spiffy->delete_file(TEST_STR_PATH);
        TEST_ASSERT_FALSE(spiffy->exists(TEST_STR_PATH));
    }
}

/**
* Scenarie: Vi laver to SPIFFS objekter på samme tid
 * Der eksisterer Spiffs objekt 1, der eksisterer spiffs objekt 2, vi bruger spiffs objekt 1 til at gemme ABCDF, vi bruger spiffs objekt 2 til at loade ABCDF
 * ABCDF er nu i arrayet, som vi har brugt til at loade
 * Vi genstarter ESP32'eren
 * Vi laver et Spiffs objekt 3, vi loader ABCDF, ABCDF er nu i arrayet
*/

void multipleSPIFFSFileManagers(){
    //Preparing the string to save and load
    const char * path2 = "/ABCDEF";
    int SIZE_OF_STR_2 = 5;
    unsigned char  STR_TO_TEST2[SIZE_OF_STR_2];
    unsigned char  STR_TO_LOAD2[SIZE_OF_STR_2];
    fill_alphanumeric_unsignedString(STR_TO_TEST2,SIZE_OF_STR_2);

    auto * spiffy2 = new SPIFFSFileManager();
    if(!didWeRestart()){
        TEST_ASSERT_FALSE(spiffy->exists(path2));
        spiffy->save_file(path2,STR_TO_TEST2);

        //We now load the array and assert they're equal
        TEST_ASSERT_TRUE(spiffy2->exists(path2));
        spiffy2->load_file(path2,STR_TO_LOAD2);
        TEST_ASSERT_EQUAL_STRING(STR_TO_TEST2,STR_TO_LOAD2);

    }
    else{

    }
    delete spiffy2;
}

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
    printf("%s","ABCDEF");
    spiffy = new SPIFFSFileManager();
    RUN_TEST(dataIsSavedAfterReboot);
    RUN_TEST(multipleSPIFFSFileManagers);

    //Tests that need to be resat above this
    if(!didWeRestart()){
        esp_restart();
    }
    RUN_TEST(fakeTest);
    UNITY_END(); // stop unit testing
}

void loop()
{
}