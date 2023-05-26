#include <esp_spiffs.h>
#include "Arduino.h"
#include "Cryptography/CryptographicSettings.h"
#include "esp_dsp.h"
#include "SPIFFS.h"
#include <FileManager.cpp>
#include "FS.h"
#include "sha/sha_parallel_engine.h"
#include "TinyGPSPlus-master/src/TinyGPS++.h"
#include "stddef.h"
#include "Utility.h"
#include "Cryptography/Cryptographer.cpp"

#include "HardwareMacros.h"


static const char* TAG_main = "Main";


const char * RSAPubKeyPath = "/RSAPubKey";
const char * RSAPrivKeyPath = "RSAPrivKey";
unsigned char PEMKeyBuffer[256];
unsigned char pubKey[pubKeyLen];
unsigned char a[2] = "a";
unsigned char outputBuf[SHA256_OUTPUT_BUFFERLEN];
unsigned char ID[IDLen];
unsigned char outputBufDecrypt[SHA256_OUTPUT_BUFFERLEN];

/**
 * Finds the size of an RSA key formatted in PEM format
 *
 * \arg PEMBUFFER: An unsigned char containing the PEM file in the format
 *                  {PEM_EMPTY_PLACEHOLDER,...,PEM_EMPTY_PLACEHOLDER,PEMFILE....,\0}
 *                  Where PEM_EMPTY_PLACEHOLDER indicates that the value is not a part of the actual PEM file.
 *
 *                  Notice, that there can be nothing inbetween the start of the PEMFILE and the end of the array.
 *
 * \return
 *          The size of the PEMFILE or PEM_ERR_NO_PEM_FILE if there is no PEM file
 */

int findStartingIndexPEMFile(unsigned char * PEMBuffer,size_t sizeOfBuffer){
    for(int i = 0; i<sizeOfBuffer;i++){
        unsigned char c = PEMBuffer[i];

        //We've reached the end of the array without encountering anything but PEM_EMPTY_PLACEHOLDERS
        if(c == '\0'){
            return PEM_ERR_NO_PEM_FILE;
        }

        if(c != PEM_EMPTY_PLACEHOLDER){
            return i;
        }

    }

    return PEM_ERR_NO_PEM_FILE;
}



bool assertNotEqualArray(unsigned char * arr1, unsigned char * arr2, size_t nrElements){
    for(int i = 0; i<nrElements;i++){
        if(arr1[i] != arr2[i]){
            return true;
        }
    }

    return false;
}


auto * rsa_Cryptographer = new RSACryptographer();




void setup(){
    Serial.begin(9600);



    int res = 0;

    Serial.println("\n___________________PROGRAM_START_________________________"); //We get a lot of fluffer at the start of the program


    //SPIFFS
    FileManager * spiff = new SPIFFSFileManager();
    int operation_result;
    //Get the key ready
    rsa_Cryptographer->generate_CTRX_context();
    operation_result = rsa_Cryptographer->generate_key();
    fs::FS fileSystem = SPIFFS;

    fileSystem.exists("/abc");


};

void loop(){

};