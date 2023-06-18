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
        throw std::logic_error("− failed to open file for writing");
    }

    //Written succesfully
    if(file.print( (const char *) dataToWrite)){
        Serial.println("− file written");
        return true;

    }
    else //Failed to write
    {
        throw std::runtime_error("− Write failed");
    }


}

bool SPIFFSFileManager::exists(const char *filePath) {
    return fileSystem.exists((const char *) filePath);
}

bool SPIFFSFileManager::delete_file(const char * filePath){
    Serial.printf("Deleting file: %s\r\n", filePath);
    if(fileSystem.remove((const char *)filePath)){
        Serial.println("− file deleted");
        return true;
    }
    else
    {
        throw std::logic_error("− delete failed");
    }
}


bool SPIFFSFileManager::load_file(const char * filePath, unsigned char * resultArray){
    File f1 = fileSystem.open(filePath);
    if(!f1 || f1.isDirectory()){
        log_e("SPIFFSFileManager: Failed to open file %s. You possibly tried to load a directory",filePath);
        throw std::logic_error("− failed to open file for reading. You possibly tried to load a directory");
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
        throw std::logic_error("− failed to open file for reading. You possibly tried to load a directory");
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
    if(!fileSystem.begin(true)){
        throw std::logic_error("SPIFFS failed to mount");
    }
    return true;
}