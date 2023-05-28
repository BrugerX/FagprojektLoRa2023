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

    /**
     *
     * Loads <= endIdx values from a file. Will automatically append \0 at the end of the array.
     *
     * @param filePath Filepath to load from, must begin with \
     * @param resultArray Where to load the array into
     * @param nrIndicesOfArray sizeOf(resultArray)/sizeOf(resultArray) or auto * array[n] => endIdx = n
     *                          |resultArray| >= endIdx
     *
     * @result resultArray now contains unsigned chars read from the file at filePath in the indices < endIdx,
     *         with resultArray[endIdx]
     */
    bool load_file(const char * filePath, unsigned char * resultArray, size_t endIdx);

    void dismount();

    bool mount();
};

#endif //FAGPROJEKTLORA2023_FILEMANAGER_H
