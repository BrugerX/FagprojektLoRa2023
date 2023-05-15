//
// Created by DripTooHard on 14-04-2023.
//

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