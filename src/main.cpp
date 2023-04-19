#include <esp_spiffs.h>
#include "Arduino.h"
#include "Cryptography/CryptographicSettings.cpp"
#include "Cryptography/RSAEncryption.h"
#include "esp_dsp.h"
#include "SPIFFS.h"
#include "Flash/CustomSPIFFS.h"
#include "Flash/FileManager.cpp"
#include "Flash/FileManager.h"
#include "FS.h"
#include "sha/sha_parallel_engine.h"
#include "TinyGPSPlus-master/src/TinyGPS++.h"
#include "stddef.h"
#include "Utility.h"
#include "Cryptography/Cryptographer.h"
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
size_t outputSize;
size_t outputSizeDecrypt;
int sizeOfKey;



TinyGPSPlus gps;

//Spiffy part of the code
esp_vfs_spiffs_conf_t SPIFFS_conf;



mbedtls_ctr_drbg_context ctr_drbg;
mbedtls_pk_context key;
int result = getready_CTRDRBG_context(&ctr_drbg);

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


void setup(){
    Serial.begin(9600);

    result = generate_keys_PK_context(&key,&ctr_drbg);


    int res = 0;

    Serial.println("___________________PROGRAM_START_________________________"); //We get a lot of fluffer at the start of the program


    //SPIFFS
    FileManager * spiff = new SPIFFSFileManager();

    RSACryptographer * rsaCryptographer = new RSACryptographer();
    unsigned char inputArray[2000];
    fill_alphanumeric_unsignedString(inputArray,sizeof(inputArray));
    println_unsignedString(inputArray,2000,CHR);
    unsigned char outputArray[256];





};

void loop(){

};