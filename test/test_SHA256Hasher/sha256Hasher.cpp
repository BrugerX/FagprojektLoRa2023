//
// Created by DripTooHard on 03-06-2023.
//

//
// Created by DripTooHard on 20-05-2023.
//


#include <Arduino.h>
#include "unity.h"
#include <Cryptographer.cpp>
#include <Hasher.h>


/**
 * IMPORTANT: Remember not to use the same paths for the tests that need to be resat; They will overwrite each other.
 */

auto * rsa_Cryptographer = new RSACryptographer();
auto * shaHasher = new SHA256Hasher();
unsigned char * CHECKSUM_ARR;
unsigned char * TEST_PEM_PUB;

void setUp(void) {
    // set stuff up here
    rsa_Cryptographer->get_key_pem(&TEST_PEM_PUB,0);
}


void tearDown(void) {
    // delete stuff down here
    fill_alphanumeric_unsignedString(CHECKSUM_ARR,sizeof(CHECKSUM_ARR)/sizeof(CHECKSUM_ARR[0]));
}

/*
 * We use the same inputs to calculate the hash into two different buffers and assert that they have the same contents
 */
void sameStringSameChecksum(){
    unsigned char * CHECKSUM_ARR2 = (unsigned char *) malloc((SHA256_OUTPUT_BUFFERLEN) * sizeof(unsigned char));

    shaHasher->generate_checksum(TEST_PEM_PUB,sizeof(TEST_PEM_PUB),CHECKSUM_ARR);
    shaHasher->generate_checksum(TEST_PEM_PUB,sizeof(TEST_PEM_PUB),CHECKSUM_ARR2);

    for(int i = 0; i<SHA256_OUTPUT_BUFFERLEN; i++){
        TEST_ASSERT_EQUAL(0,CHECKSUM_ARR2[i]^CHECKSUM_ARR[i]);
    }
    free(CHECKSUM_ARR2);
}

/*
 * We calculate the checksum twice using the same input, but with different SHA256Hasher objects
 * We then assert, that they're the same checksums
 */
void differentHashersSameInputSameChecksum(){
    auto * temp_hasher = new SHA256Hasher();
    unsigned char * CHECKSUM_ARR2 = (unsigned char *) malloc((SHA256_OUTPUT_BUFFERLEN) * sizeof(unsigned char));

    temp_hasher->generate_checksum(TEST_PEM_PUB,sizeof(TEST_PEM_PUB),CHECKSUM_ARR);
    shaHasher->generate_checksum(TEST_PEM_PUB,sizeof(TEST_PEM_PUB),CHECKSUM_ARR2);

    for(int i = 0; i<SHA256_OUTPUT_BUFFERLEN; i++)
    {
        TEST_ASSERT_EQUAL(0,CHECKSUM_ARR2[i]^CHECKSUM_ARR[i]);
    }

    free(CHECKSUM_ARR2);
}



void setup()
{
    delay(5000); // service delay

    //DON'T PUT ANYTHING BEFORE THIS EXCEPT FOR DELAY!!!!
    UNITY_BEGIN(); //Define stuff after this
    rsa_Cryptographer->generate_CTRX_context();
    rsa_Cryptographer->generate_key();
    CHECKSUM_ARR = (unsigned char *) malloc(SHA256_OUTPUT_BUFFERLEN * sizeof(unsigned char));
    TEST_PEM_PUB = (unsigned char *) malloc(PEMPubKeyLen*sizeof(unsigned char));
    RUN_TEST(sameStringSameChecksum);
    RUN_TEST(differentHashersSameInputSameChecksum);
    UNITY_END(); // stop unit testing
}

void loop()
{
}
