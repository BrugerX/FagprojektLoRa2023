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


SPIFFSFileManager::SPIFFSFileManager()
{
    //We have to mount the spiffs
    if(!mount()){
        Serial.println("COULD NOT MOUNT SPIFFS");
        throw std::runtime_error("COULD NOT MOUNT SPIFFS");
    }
}


SPIFFSFileManager::~SPIFFSFileManager(){
}

bool SPIFFSFileManager::save_file(const char *filePath, const unsigned char *dataToWrite) {
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

    file.close();

}

bool SPIFFSFileManager::exists(const char *filePath) {
    return fileSystem.exists((const char *) filePath);
}

bool SPIFFSFileManager::delete_file(const char * filePath){
    Serial.printf("Deleting file: %s\r\n", filePath);
    if(fileSystem.remove((const char *)filePath)){
        Serial.println("− file deleted");
        return true;
    } else {
        Serial.println("− delete failed");
        return false;
    }
}


bool SPIFFSFileManager::load_file(const char * filePath, unsigned char * resultArray){
    File f1 = fileSystem.open(filePath);
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

bool SPIFFSFileManager::load_file(const char * filePath, unsigned char * resultArray, size_t endIdx){
    File f1 = fileSystem.open(filePath,FILE_READ);
    if(!f1 || f1.isDirectory()){
        Serial.println("− failed to open file for reading");
        return false;
    }

    unsigned char res;

    for (int i = 0; i<endIdx; i++){
        if(!f1.available()){
            break;
        }
        res = f1.read();
        resultArray[i] = res;
    }

    resultArray[endIdx] = '\0';

    return true;

}


void SPIFFSFileManager::dismount() {
    fileSystem.end();
}

//TODO: Default arguments ift. basepath + partition label
bool SPIFFSFileManager::mount() {
    return fileSystem.begin(true);
}