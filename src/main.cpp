#include <esp_spiffs.h>
#include "Arduino.h"
#include <CryptographicSettings.h>
#include "esp_dsp.h"
#include <FileManager.cpp>
#include "stddef.h"
#include "../lib/Utility/Utility.h"
#include <Cryptographer.cpp>
#include "sha/sha_parallel_engine.h"
#include "mbedtls/sha256.h"
#include "Hasher.h"


static const char* TAG_main = "Main";


const char * RSAPubKeyPath = "/RSAPubKey";
const char * RSAPrivKeyPath = "/RSAPrivKey";
unsigned char outputBuf[SHA256_OUTPUT_BUFFERLEN];
unsigned char ID[IDLen];

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



auto * rsa_Cryptographer = new RSACryptographer();

auto * hashishi = new SHA256Hasher();



void setup(){
    Serial.begin(9600);

    fill_char_unsignedString(ID,IDLen,'A');


    int res = 0;

    Serial.println("\n___________________PROGRAM_START_________________________"); //We get a lot of fluffer at the start of the program


    //SPIFFS
    auto * spiff = new SPIFFSFileManager();
    unsigned char * pub,*priv;
    auto * pub_to_load = (unsigned char *) malloc(PEMPubKeyLen * sizeof(unsigned char));
    auto * priv_to_load = (unsigned char *) malloc(PEMPrivKeyLen * sizeof(unsigned char));

    rsa_Cryptographer->generate_CTRX_context();
    rsa_Cryptographer->generate_key();

    rsa_Cryptographer->get_key_pem(&pub,0);
    rsa_Cryptographer->get_key_pem(&priv,1);

    spiff->save_file(RSAPubKeyPath,pub);
    spiff->save_file(RSAPrivKeyPath,priv);

    spiff->load_file(RSAPubKeyPath,pub_to_load,PEMPubKeyLen-1);
    spiff->load_file(RSAPrivKeyPath,priv_to_load,PEMPrivKeyLen-1);
    println_unsignedString(priv_to_load,CHR);


    res = rsa_Cryptographer->load_key_pem(pub_to_load,0);
    if(!isGoodResult(res)){
        Serial.print("FAILED TO LOAD PUB KEY PEM");
    }

    res = rsa_Cryptographer->load_key_pem(priv_to_load,1);
    if(!isGoodResult(res)){
        Serial.print("FAILED TO LOAD PRIV KEY PEM");
    }

    res = rsa_Cryptographer->validate_key();
    if(!isGoodResult(res)){
        Serial.print("NONO MISTAH!");
    }

    hashishi->generate_checksum(ID,IDLen,outputBuf);
    println_unsignedString(outputBuf,SHA256_OUTPUT_BUFFERLEN,HEX);
    fill_alphanumeric_unsignedString(outputBuf,SHA256_OUTPUT_BUFFERLEN);
    hashishi->generate_checksum(ID,IDLen,outputBuf);
    println_unsignedString(outputBuf,SHA256_OUTPUT_BUFFERLEN,HEX);

};

void loop(){

};