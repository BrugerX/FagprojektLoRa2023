#include <esp_spiffs.h>
#include "Arduino.h"
#include <CryptographicSettings.h>
#include "esp_dsp.h"
#include "stddef.h"
#include <FileManager.h>
#include "UnsignedStringUtility.h"
#include <Cryptographer.cpp>
#include "sha/sha_parallel_engine.h"
#include "mbedtls/sha256.h"
#include "Hasher.h"
#include "regex"
#include <RegexUtility.h>
#include <RSAPEMHandler.h>
#include "../lib/MVC/DataView.h"
#include "../lib/MVC/DataController.h"
#include "../lib/MVC/MVCSettings.h"
#include <cstdlib>

#define CHR 0
#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2


static const char* TAG_main = "Main";


const char * RSAPubKeyPath = "/RSAPubKey";
const char * RSAPrivKeyPath = "/RSAPrivKey";
unsigned char outputBuf[SHA256_OUTPUT_BUFFERLEN];
unsigned char ID[IDLen];
DataView dataView = DataView();
DataController dataController = DataController(&dataView);
char names[6][8] = {"Bjarke", "Benny", "Birger", "Bjarne", "Bent", "Birk"};



auto * rsa_Cryptographer = new RSACryptographer();


auto * PEMHandler = new RSAPEMHandler();


void setup(){
    Serial.begin(9600);
    delay(2000);
    dataView.initialiseView();

    dataView.showStartScreen(); //to initialise start screen

    for(int i = 0; i < 6; i++){
        srand(i);
        dataController.addGroupMember(Member(names[i], NavigationData()));
    }
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



    res = rsa_Cryptographer->parse_key_pem(pub_to_load, 0);
    if(!isGoodResult(res)){
        Serial.print("FAILED TO LOAD PUB KEY PEM");
    }

    res = rsa_Cryptographer->parse_key_pem(priv_to_load, 1);
    if(!isGoodResult(res)){
        Serial.print("FAILED TO LOAD PRIV KEY PEM");
    }


};
char input = ' ';
void loop(){
  if(Serial.available() != 0){
        Serial.println("Ready to read");
        input = (char) Serial.read();
        if(input != 10){
            Serial.print("char is: " );
            Serial.println(input);
            dataController.handleUserInput(input);
        }
   }
};