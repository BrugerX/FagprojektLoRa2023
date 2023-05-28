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
    spiffy->mount();
}

void fakeTest(){
    TEST_ASSERT_EQUAL_MESSAGE(true,true,(char *) didWeRestart());
    TEST_ASSERT_TRUE(true);
}

void dataIsSavedAndLoadedCorrectly(){
    unsigned char STR_TO_LOAD[sizeof(TEST_STR)];
    TEST_ASSERT_TRUE(spiffy->save_file(TEST_STR_PATH,(unsigned char *)TEST_STR));
    TEST_ASSERT_TRUE(spiffy->load_file(TEST_STR_PATH,STR_TO_LOAD,sizeof(STR_TO_LOAD)-1));
    TEST_ASSERT_EQUAL_STRING(TEST_STR,STR_TO_LOAD);
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
        spiffy->save_file(TEST_STR_PATH,(const unsigned char *) TEST_STR);
        TEST_ASSERT_TRUE(spiffy->exists(TEST_STR_PATH));
    }
    //After the reset we check to see if it still exists, if we can load it, we then delete it
    else{
        TEST_ASSERT_TRUE(spiffy->exists(TEST_STR_PATH));
        unsigned char load_result_arr[sizeof(TEST_STR)];
        spiffy->load_file(TEST_STR_PATH,load_result_arr,sizeof(load_result_arr)-1);

        //Time to delete it
        TEST_ASSERT_EQUAL_STRING((unsigned char *) TEST_STR,load_result_arr);
        spiffy->delete_file(TEST_STR_PATH);
        TEST_ASSERT_FALSE(spiffy->exists(TEST_STR_PATH));
    }
}

/**
* Scenarie: Vi har to SPIFFS objekter på samme tid, men kun det ene kan operere på SPIFFS
 * Spiffy gemmer et array og bekræfter, at det eksisterer samt loade det
 * Spiffy2 prøver at bekræfte, at det eksisterer, men det gør det ikke
 * Spiffy2 prøver at loade arrayet, men det kan ikke
 * Spiffy dismounter, Spiffy2 kan nu loade og bekræfte arrayets eksistens
 * Spiffy kan ikke loade eller bekræfte
*/

void multipleSPIFFSFileManagers(){

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

    //Tests that need to be resat above this
    if(!didWeRestart()){
        esp_restart();
    }

    RUN_TEST(dataIsSavedAndLoadedCorrectly);
    RUN_TEST(multipleSPIFFSFileManagers);
    UNITY_END(); // stop unit testing
}

void loop()
{
}