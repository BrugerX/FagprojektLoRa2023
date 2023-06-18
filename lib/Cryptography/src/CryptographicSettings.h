//
// Created by DripTooHard on 16-05-2023.
//

#ifndef FAGPROJEKTLORA2023_CRYPTOGRAPHICSETTINGS_H
#define FAGPROJEKTLORA2023_CRYPTOGRAPHICSETTINGS_H

//
// Created by DripTooHard on 03-04-2023.
//

//Truth values for our RSA functions
//They're defined as such, because the mbedtls libraries define 0 as success
#define RSABooleanTrue 0
#define RSABooleanFalse 1


//RSA related
#define RSAPubKeyEXPONENT 65537
#define pubKeyLen 256*8 //2048 bits
#define RSA_MAX_INPUT_LEN 245 //245 bytes

//RSA related errors
#define RSA_ERR_INPUT_EXCEEDS_MAX_LEN -69
#define RSA_ERR_OUTPUT_EXCEEDS_OUTPUT_ARRAY_LEN -68

//Identification/Network related
#define IDLen 20 //How many of the chars we take from the hash

//If we iterate over a PEM file and it's "7"
#define PEM_EMPTY_PLACEHOLDER 100
#define PEM_ERR_NO_PEM_FILE -69
#define PEMPubKeyLen 1500 //Default size of the arrays used to store the public key PEM arrays
#define PEMPrivKeyLen 1800

//Hashing related
#define SHA256_OUTPUT_BUFFERLEN 32 //256 bits
#define SHA256_ERR_CTX_IS_NULL -53712


/**
 *  FUNCTIONS
 */

bool isGoodResult(int res);
#endif //FAGPROJEKTLORA2023_CRYPTOGRAPHICSETTINGS_H
