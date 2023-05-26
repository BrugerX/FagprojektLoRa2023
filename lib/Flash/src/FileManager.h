//
// Created by DripTooHard on 14-04-2023.
//

#ifndef FAGPROJEKTLORA2023_FILEMANAGER_H
#define FAGPROJEKTLORA2023_FILEMANAGER_H

#include "SPIFFS.h"


class FileManager;

class SPIFFSFileManager{

private:

    fs::SPIFFSFS fileSystem;

public:
    SPIFFSFileManager();
    ~SPIFFSFileManager();
    /**
     * Saves a file to the flash using SPIFFs
     *
     * \return true if a success, false if a failure, prints a custom error message
     */
    bool save_file(const char * filePath, const unsigned char * dataToWrite);

    bool exists(const char * filePath);

    bool delete_file(const char * filePath);

    bool load_file(const char * filePath, unsigned char * resultArray);
};

#endif //FAGPROJEKTLORA2023_FILEMANAGER_H
