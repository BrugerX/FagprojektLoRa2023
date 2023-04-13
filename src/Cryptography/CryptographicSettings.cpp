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

//Identification/Network related
#define IDLen 20 //How many of the chars we take from the hash

//Hashing related
#define SHA256_OUTPUT_BUFFERLEN 32 //256 bits