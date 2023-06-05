#include <esp_spiffs.h>
#include "Arduino.h"
#include <CryptographicSettings.h>
#include "esp_dsp.h"
#include "stddef.h"
#include <FileManager.h>
#include "../lib/Utility/Utility.h"
#include <Cryptographer.cpp>
#include "sha/sha_parallel_engine.h"
#include "mbedtls/sha256.h"
#include "Hasher.h"
#include "regex"
#include <RegexUtility.h>
#include <RSAPEMHandler.h>


static const char* TAG_main = "Main";


const char * RSAPubKeyPath = "/RSAPubKey";
const char * RSAPrivKeyPath = "/RSAPrivKey";
unsigned char outputBuf[SHA256_OUTPUT_BUFFERLEN];
unsigned char ID[IDLen];





auto * rsa_Cryptographer = new RSACryptographer();

auto * hashishi = new SHA256Hasher();

auto * PEMHandler = new RSAPEMHandler();


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
    println_unsignedString(pub_to_load,PEMPubKeyLen,CHR);

    int IDXs[2];
    PEMHandler->getIDXs(pub_to_load,PEMPubKeyLen,IDXs);
    int startingIdx = IDXs[0];
    int endIdx = IDXs[1];

    unsigned char * source;
    size_t source_size;

    if(startingIdx>-1)
    {
        println_unsignedString(pub_to_load+startingIdx,PEMPubKeyLen - (PEMPubKeyLen-endIdx) - (startingIdx+1),CHR);
    }
    else{
        Serial.println("Huh??!");
    }

    PEMHandler->getSource(pub_to_load,PEMPubKeyLen,&source,&source_size);
    println_unsignedString(source,source_size,CHR);


};

void loop(){

};