
//
// Created by DripTooHard on 13-04-2023.
//

#ifndef FAGPROJEKTLORA2023_CUSTOMSPIFFS_H
#define FAGPROJEKTLORA2023_CUSTOMSPIFFS_H
#include "Arduino.h"
#include "SPIFFS.h"


void listDir(fs::FS &fs, const char * dirname, uint8_t levels);

void readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
void deleteFile(fs::FS &fs, const char * path);
void renameFile(fs::FS &fs, const char * path1, const char * path2);
void appendFile(fs::FS &fs, const char * path, const char * message);

#endif //FAGPROJEKTLORA2023_CUSTOMSPIFFS_H