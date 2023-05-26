//
// Created by DripTooHard on 14-04-2023.
//

#include "FileManager.h"

class FileManager{
public:
    FileManager(){}
    virtual ~FileManager(){}
    virtual bool save_file(const char * filePath, const unsigned char * dataToWrite) = 0;
    virtual bool load_file(const char * filePath, unsigned char * resultArray) = 0;
    virtual bool delete_file(const char * filePath) = 0;
    virtual bool exists(const char * filePath) = 0;
};

/**
 * Whenever we deconstruct the SPIFFSFileManager, we unmount the SPIFFs module.
 */
class SPIFFSFileManager : public FileManager{

private:
    fs::FS fileSystem = SPIFFS;

public:

    SPIFFSFileManager()
    {
    //We have to mount the spiffs
    SPIFFS.begin(true);
    }

    ~SPIFFSFileManager(){
        SPIFFS.end();
    }

    /**
     * Saves a file to the flash using SPIFFs
     *
     * \return true if a success, false if a failure, prints a custom error message
     */
    bool save_file(const char * filePath, const unsigned char * dataToWrite){
        Serial.printf("Writing file: %s\r\n", filePath);

        File file = fileSystem.open((const char *)filePath, FILE_WRITE);

        //Failed to open
        if(!file){
            Serial.println("− failed to open file for writing");
            return false;
        }

        //Written succesfully
        if(file.print( (const char *) dataToWrite)){
            Serial.println("− file written");
            return true;

        //Failed to write
        }else {
            Serial.println("− frite failed");
            return false;
        }
    }

    bool exists(const char * filePath){
        return fileSystem.exists((const char *) filePath);
    }

    bool delete_file(const char * filePath){
        Serial.printf("Deleting file: %s\r\n", filePath);
        if(fileSystem.remove((const char *)filePath)){
            Serial.println("− file deleted");
            return true;
        } else {
            Serial.println("− delete failed");
            return false;
        }
    }

    bool load_file(const char * filePath, unsigned char * resultArray){
        File f1 = SPIFFS.open(filePath);
        if(!f1 || f1.isDirectory()){
            Serial.println("− failed to open file for reading");
            return false;
        }

        int i = 0;
        unsigned char res;

        while(f1.available()){
            res = f1.read();
            resultArray[i++] = res;
        }

        return true;

    }
};