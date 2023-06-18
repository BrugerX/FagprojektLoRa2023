//
// Created by DripTooHard on 20-05-2023.
//


#include <Arduino.h>
#include <unity.h>
#include "../../lib/Utility/Utility.cpp"
#include <FileManager.cpp>
#include "esp_system.h"
#include <TestUtility.h>



/**
 * IMPORTANT: Remember not to use the same paths for the tests that need to be resat; They will overwrite each other.
 */
const char * TEST_STR_PATH;
char TEST_STR[] = "ABC";;
SPIFFSFileManager * spiffy;
int testInt;


void deleteSaveLoadString(SPIFFSFileManager * spiffsFileManager,const char * PATH_OF_STR,unsigned char * STR_TO_TEST, size_t endIdx){
    unsigned char STR_TO_LOAD[endIdx+1];
    if(spiffsFileManager->exists(PATH_OF_STR))
    {
    spiffsFileManager->delete_file(PATH_OF_STR);
    }
    TEST_ASSERT_FALSE(spiffsFileManager->exists(PATH_OF_STR));
    TEST_ASSERT_TRUE(spiffsFileManager->save_file(PATH_OF_STR,STR_TO_TEST));
    TEST_ASSERT_TRUE(spiffsFileManager->load_file(PATH_OF_STR,STR_TO_LOAD,endIdx));
    TEST_ASSERT_EQUAL_STRING(STR_TO_TEST,STR_TO_LOAD);
}

bool didWeRestart(){
    return  esp_reset_reason() == ESP_RST_SW;
}

void setUp(void) {
    // set stuff up here
    TEST_STR_PATH = "/abc";
}


void tearDown(void) {
    // delete stuff down here
    spiffy->mount();
}


void dataIsSavedAndLoadedCorrectly(){
    deleteSaveLoadString(spiffy,TEST_STR_PATH,(unsigned char *) TEST_STR,sizeof(TEST_STR)/sizeof(TEST_STR[0])-1);
    TEST_ASSERT_TRUE(spiffy->delete_file(TEST_STR_PATH));
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
        unsigned char load_result_arr[sizeof(TEST_STR)/sizeof(TEST_STR[0])];
        fill_alphanumeric_unsignedString(load_result_arr,sizeof(TEST_STR));
        spiffy->load_file(TEST_STR_PATH,load_result_arr,sizeof(load_result_arr)-1);

        //Time to delete it
        TEST_ASSERT_EQUAL_STRING((unsigned char *) TEST_STR,load_result_arr);
        spiffy->delete_file(TEST_STR_PATH);
        TEST_ASSERT_FALSE(spiffy->exists(TEST_STR_PATH));
    }
}

//TODO: TRANSLATE THIS TO ENGLISH
/**
* Scenarie: Vi har to SPIFFS objekter på samme tid, men kun det ene kan operere på SPIFFS
 * Spiffy gemmer et array og bekræfter, at det eksisterer samt loade det
 * Spiffy2 prøver at bekræfte, at det eksisterer, men det gør det ikke
 * Spiffy2 prøver at loade arrayet, men det kan ikke
 * Spiffy dismounter, Spiffy2 kan nu loade og bekræfte arrayets eksistens
 * Spiffy kan ikke loade eller bekræfte
*/

void multipleSPIFFSFileManagers(){
    //Preparing the string to save and load
    const char * path2 = "/paf2";
    int SIZE_OF_STR_2 = 5;
    unsigned char  STR_TO_TEST2[SIZE_OF_STR_2 +1];
    unsigned char  STR_TO_LOAD2[SIZE_OF_STR_2 +1];
    STR_TO_TEST2[SIZE_OF_STR_2] = '\0';
    fill_alphanumeric_unsignedString(STR_TO_TEST2,SIZE_OF_STR_2);

    auto * spiffy2 = new SPIFFSFileManager();
    //First we save it, assert that it exists and that we can load it using spiffy
    deleteSaveLoadString(spiffy,path2,STR_TO_TEST2,SIZE_OF_STR_2);

    //We now fill the string with the same char
    fill_char_unsignedString(STR_TO_LOAD2,SIZE_OF_STR_2,'A');


    //We now confirm that spiffy2 cannot load the array
    TEST_ASSERT_FALSE(spiffy2->exists(path2));
    try{
        TEST_ASSERT_TRUE(spiffy2->load_file(path2,STR_TO_LOAD2));
        TEST_FAIL_MESSAGE("IT WAS POSSIBLE TO LOAD THE FILE");
    }
    catch (std::logic_error ){};

    //We now dismount spiffy, mount spiffy2 again and redo all the operations we did with spiffy this time with spiffy2
    spiffy->dismount();
    spiffy2->mount();

    deleteSaveLoadString(spiffy2,path2,STR_TO_TEST2,SIZE_OF_STR_2);


    //Finally we confirm that spiffy cannot load the array, now that spiffy2 is mounted
    TEST_ASSERT_FALSE(spiffy->exists(path2));
    try{
        TEST_ASSERT_TRUE(spiffy->load_file(path2,STR_TO_LOAD2));
        TEST_FAIL_MESSAGE("IT WAS POSSIBLE TO LOAD THE FILE");
    }
    catch (std::logic_error ){};

    spiffy2->dismount();
    spiffy->mount();

    delete spiffy2;
}


void setup()
{
    delay(5000); // service delay

    //DON'T PUT ANYTHING BEFORE THIS EXCEPT FOR DELAY!!!!
    UNITY_BEGIN(); //Define stuff after this
    spiffy = new SPIFFSFileManager();
    RUN_TEST(dataIsSavedAfterReboot);

    //Tests that need to be resat are placed above this and run twice
    if(!didWeRestart()){
        log_i("REBOOTING THE SPIFFSMANAGER TEST NOW");
        esp_restart();
    }

    //Tests where we don't check what happens after reset, below here, run once
    RUN_TEST(dataIsSavedAndLoadedCorrectly);
    RUN_TEST(multipleSPIFFSFileManagers);
    UNITY_END(); // stop unit testing
}

void loop()
{
}