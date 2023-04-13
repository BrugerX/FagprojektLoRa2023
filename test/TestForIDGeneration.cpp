/*
 * Created by: DripTooHard
 *
 * Purpose: A pseudo-unit test for checking the various functions related to RSA encryption
 */
/*
#include "Arduino.h"
#include "mbedtls/sha256.h"
#include "sha/sha_parallel_engine.h"
#include "Cryptography/CryptographicSettings.cpp"
#include "esp_dsp.h"
#include "SPIFFS.h"
#include "stddef.h"
#include "utility.h"
#include "Cryptography/RSACryptography.h"


static const char* TAG_main = "Main";

unsigned char pubKey[pubKeyLen];
unsigned char a[2] = "0";
unsigned char outputBuf[SHA256_OUTPUT_BUFFERLEN];
unsigned char ID[IDLen];
unsigned char outputBufDecrypt[SHA256_OUTPUT_BUFFERLEN];
size_t outputSize;
size_t outputSizeDecrypt;
unsigned char IDEncrypted[65];




mbedtls_ctr_drbg_context ctr_drbg;
mbedtls_pk_context key;
int result = getready_CTRDRBG_context(&ctr_drbg);







void setup(){
    Serial.begin(9600);


    result = generate_keys_PK_context(&key,&ctr_drbg);

    int res = 0;

    Serial.println("___________________PROGRAM_START_________________________"); //We get a lot of fluffer at the start of the program

    for(int i = 0;i<IDLen;i++){
        ID[i] = a[0];
        a[0] += 1;
        if(a[0]>100){
            a[0] = 48;
        }
    }

    println_unsignedString(ID,SHA256_OUTPUT_BUFFERLEN,CHR);


    Serial.println("Checking to see if the context contains a public key");
    res = mbedtls_rsa_check_pubkey(mbedtls_pk_rsa(key));
    if(res != RSABooleanTrue){
        Serial.println("ERROR: Context does not contain public key!");
        Serial.println(res);
    }

    Serial.println("Checking to see if the context contains a private key");
    res = mbedtls_rsa_check_privkey(mbedtls_pk_rsa(key));
    if(res != RSABooleanTrue){
        Serial.println("ERROR: Context does not contain private key!");
        Serial.println(res);
    }



    //Scenario: Generating RSA keypair
    Serial.println("Checking to see if the public and private keys of the context match up");
    res = mbedtls_rsa_check_pub_priv(mbedtls_pk_rsa(key),mbedtls_pk_rsa(key));
    if(res != RSABooleanTrue){
        Serial.println("ERROR: Pub and private key do not match up!");
        Serial.println(res);
    }

    //Scenario: Checking if the keys work
    Serial.println("Checking to see if the context can de- and encrypt");
    Serial.println(&"Given we had an ID of length" [ IDLen]);
    println_unsignedString(ID,IDLen,CHR);
    Serial.println("Then if we use our PK key context to encrypt the ID, we should get:");
    Serial.println("5A1D647DA7813345C1D777A74D7EE365766513415C565ECE9D565354F8BB644F");

    //IMPLEMENT TEST

    Serial.println("Then if we decrypt it using the same PK key context, we should get our original ID back");

    //IMPLEMENT TEST

    //Test scenarie: Gem ID og genstart ESP
    // Se om ID eksisterer
    // Se om ID er korrekt længde
    // Se om ID er af korrekt indhold

    //Test scenarie: Gem pub og private key og genstart ESP
    //Se om pub eksisterer
    //Se om private eksisterer
    //Se om public key virker
    //Se om private key virker



};

void loop(){


    mbedtls_pk_encrypt(&key,(const unsigned char *) ID, (size_t) IDLen,outputBuf, &outputSize,(size_t) SHA256_OUTPUT_BUFFERLEN,mbedtls_ctr_drbg_random, &ctr_drbg);
    println_unsignedString(outputBuf, outputSize,HEX);
    Serial.println("_________________-");
    mbedtls_pk_decrypt(&key,(const unsigned char *) outputBuf, (size_t) outputSize,outputBufDecrypt, &outputSizeDecrypt,(size_t) SHA256_OUTPUT_BUFFERLEN,mbedtls_ctr_drbg_random, &ctr_drbg);
    println_unsignedString(outputBufDecrypt, outputSizeDecrypt,CHR);
    Serial.println("_________________-");
    delay(1000000);


};*/