//
// Created by DripTooHard on 03-04-2023.
//

//Truth values for our RSA functions
//They're defined as such, because the mbedtls libraries define 0 as success
#define RSABooleanTrue 0
#define RSABooleanFalse 1

//RSA related
#define RSAPubKeyEXPONENT 65537
#define pubKeyLen 256 //2048 bits
#define RSA_MAX_INPUT_LEN 245 //245 bytes

//RSA related errors
#define RSA_ERR_INPUT_EXCEEDS_MAX_LEN -69

//Identification/Network related
#define IDLen 20 //How many of the chars we take from the hash

//If we iterate over a PEM file and it's "7"
#define PEM_EMPTY_PLACEHOLDER 7
#define PEM_ERR_NO_PEM_FILE -69

//Hashing related
#define SHA256_OUTPUT_BUFFERLEN 32 //256 bits