//
// Created by DripTooHard on 14-05-2023.
//

#include <Arduino.h>
#include <unity.h>
#include "Utility.cpp"
#include "Cryptography/CryptographicSettings.cpp"
#include "Cryptography/Cryptographer.cpp"

//
// Created by DripTooHard on 14-05-2023.
//




unsigned char STR_TO_ENCRYPT[10];
unsigned char OUTPUT_ARRAY[300];
RSACryptographer rsa_Cryptographer;
int operation_result;
size_t oLen;

bool isGoodResult(int res){
    return operation_result == RSABooleanTrue;
}

void setUp(void) {
    // set stuff up here
    fill_alphanumeric_unsignedString(STR_TO_ENCRYPT,sizeof(STR_TO_ENCRYPT));
}


void tearDown(void){
    // delete stuff down here
    fill_char_unsignedString(STR_TO_ENCRYPT,sizeof(STR_TO_ENCRYPT),0);
    fill_char_unsignedString(OUTPUT_ARRAY,sizeof(OUTPUT_ARRAY),0);
    operation_result = 600;
}

//The input size is too big for the RSA algorithm
void inputIsBiggerThanMaxInput(){
    unsigned char INPUT_ARR[RSA_MAX_INPUT_LEN+1];
    operation_result = rsa_Cryptographer.encrypt(INPUT_ARR, sizeof(INPUT_ARR), OUTPUT_ARRAY, sizeof(OUTPUT_ARRAY), &oLen);
    TEST_ASSERT_EQUAL(RSA_ERR_INPUT_EXCEEDS_MAX_LEN,operation_result);

};

void inputIsSameSizeAsMaxInput(){
    unsigned char INPUT_ARR[RSA_MAX_INPUT_LEN];
    operation_result = rsa_Cryptographer.encrypt(INPUT_ARR, sizeof(INPUT_ARR), OUTPUT_ARRAY, sizeof(OUTPUT_ARRAY), &oLen);
    TEST_ASSERT_EQUAL(RSABooleanTrue,operation_result);
}

//The output length is too big for the RSA algorithm
void outLenIsBiggerThanOutputArray(){
    unsigned char TEST_OUT[30];
    operation_result = rsa_Cryptographer.encrypt(STR_TO_ENCRYPT,sizeof(STR_TO_ENCRYPT), TEST_OUT, sizeof(TEST_OUT), &oLen);
    TEST_ASSERT_EQUAL(RSA_ERR_OUTPUT_EXCEEDS_OUTPUT_ARRAY_LEN,operation_result);
}

//Encryption and decryption work if you decrypt the plaintext into the array containing the cyphertext
void encrypt_decryptInPlace(){
    operation_result = rsa_Cryptographer.encrypt(STR_TO_ENCRYPT,sizeof(STR_TO_ENCRYPT), OUTPUT_ARRAY, sizeof(OUTPUT_ARRAY), &oLen);

    if(!isGoodResult(operation_result)){
        TEST_FAIL_MESSAGE("ENCRYPTION FAILED");
    }


    operation_result = rsa_Cryptographer.decrypt(OUTPUT_ARRAY,oLen,OUTPUT_ARRAY,sizeof(OUTPUT_ARRAY),&oLen);

    if(!isGoodResult(operation_result)){
        TEST_FAIL_MESSAGE("DECRYPTION FAILED");
    }

    TEST_ASSERT_EQUAL_STRING(STR_TO_ENCRYPT,OUTPUT_ARRAY);
}


void setup()
{
    delay(5000); // service delay


    UNITY_BEGIN(); //Define stuff after this
    rsa_Cryptographer.generate_CTRX_context();
    rsa_Cryptographer.generate_key();

    RUN_TEST(inputIsBiggerThanMaxInput);
    RUN_TEST(inputIsSameSizeAsMaxInput);
    RUN_TEST(outLenIsBiggerThanOutputArray);
    RUN_TEST(encrypt_decryptInPlace);


    UNITY_END(); // stop unit testing
}

void loop()
{
}