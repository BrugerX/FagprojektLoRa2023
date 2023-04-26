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


mbedtls_ctr_drbg_context ctr_CTX;
mbedtls_pk_context RSA_ctx;




void setup(){
    Serial.begin(9600);



    int res = 0;

    Serial.println("___________________PROGRAM_START_________________________"); //We get a lot of fluffer at the start of the program


    //SPIFFS
    FileManager * spiff = new SPIFFSFileManager();

    /*
    auto * rsaCryptographer = new RSACryptographer();

    if(rsaCryptographer->generate_CTRX_context() != 0){
        Serial.println("Error generating CTR");
    }
    if(rsaCryptographer->generate_key() != 0){
        Serial.println("Error");
    }

    if(rsaCryptographer->validate_key() != 0){
        Serial.println("Error");
    }*/

    getready_CTRDRBG_context(&ctr_CTX);
    generate_keys_PK_context(&RSA_ctx,&ctr_CTX);

    unsigned char inputArray[30];
    unsigned char outputArray[4000];
    size_t oLen;

    fill_alphanumeric_unsignedString(inputArray,sizeof(inputArray));
    println_unsignedString(inputArray,sizeof(inputArray),CHR);

    res = rsaCryptographer->encrypt(inputArray,sizeof(inputArray),outputArray,sizeof(outputArray),&oLen);
    if(res != 0){
        Serial.println("Error encrypting");
        Serial.println(res);
    }


    println_unsignedString(outputArray,sizeof(inputArray),CHR);


    //fill_alphanumeric_unsignedString(outputArray,sizeof(outputArray));
    rsaCryptographer->decrypt(outputArray,oLen,outputArray,sizeof(outputArray),&oLen);

    //mbedtls_pk_encrypt(&key,(const unsigned char *)inputArray,sizeof(inputArray),outputArray,&oLen,sizeof(outputArray),mbedtls_ctr_drbg_random,&ctr_drbg);
    println_unsignedString(outputArray,oLen,CHR);



};

void loop(){

};