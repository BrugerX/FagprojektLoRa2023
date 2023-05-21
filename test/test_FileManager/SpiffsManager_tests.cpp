//
// Created by DripTooHard on 20-05-2023.
//

#include <Arduino.h>
#include <unity.h>
#include "Utility.cpp"
#include "Flash/FileManager.h"


void setUp(void) {
    // set stuff up here

}


void tearDown(void) {
    // delete stuff down here
    int a;
}


/**
* Scenarie: Vi gemmer ABCDEF, genstarter ESP32'eren, og det eksisterer,
*
 */

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

    UNITY_END(); // stop unit testing
}

void loop()
{
}