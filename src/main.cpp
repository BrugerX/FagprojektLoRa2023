#include <esp_spiffs.h>
#include "Arduino.h"
#include <CryptographicSettings.h>
#include "esp_dsp.h"
#include "SPIFFS.h"
#include <FileManager.cpp>
#include "FS.h"
#include "sha/sha_parallel_engine.h"
#include "TinyGPSPlus-master/src/TinyGPS++.h"
#include "stddef.h"
#include "../lib/Utility/Utility.h"
#include <Cryptographer.cpp>

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
    auto * spiff = new SPIFFSFileManager();
    char * STR_FILE_PATH = "/ABC";
    int SIZE_OF_FILE = 3;
    unsigned char STR_FILE[SIZE_OF_FILE+1];
    unsigned char load_buffer[SIZE_OF_FILE+1];

    fill_alphanumeric_unsignedString(STR_FILE,SIZE_OF_FILE);
    println_unsignedString(STR_FILE,sizeof(STR_FILE),CHR);

    if(esp_reset_reason() != ESP_RST_SW) {
        spiff->save_file(STR_FILE_PATH, (unsigned char *) STR_FILE);
        esp_restart();
    }
    else{
    spiff->load_file(STR_FILE_PATH,load_buffer,(int) sizeof(load_buffer));
    Serial.print("Loaded file:");
    println_unsignedString(load_buffer,SIZE_OF_FILE,CHR);

    for(int i = 0; i<sizeof(load_buffer);i++){
        assert(load_buffer[i] == STR_FILE[i]);
    }

    for(int i = 0; load_buffer[i];i++){
        Serial.print(load_buffer[i],HEX);
        Serial.print(",");
    }
    }

};

void loop(){

};