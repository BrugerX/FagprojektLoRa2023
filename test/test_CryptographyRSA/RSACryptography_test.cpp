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


int encryptDecrypt(RSACryptographer rsaCrypto){
    operation_result = rsaCrypto.encrypt(STR_TO_ENCRYPT,sizeof(STR_TO_ENCRYPT), OUTPUT_ARRAY, sizeof(OUTPUT_ARRAY), &oLen);

    if(!isGoodResult(operation_result)){
        return operation_result;
    }

    operation_result = rsaCrypto.decrypt(OUTPUT_ARRAY,oLen,OUTPUT_ARRAY,sizeof(OUTPUT_ARRAY),&oLen);

    if(!isGoodResult(operation_result)){
        return operation_result;
    }

    return 0;

}

bool assertNotEqualArray(unsigned char * arr1, unsigned char * arr2, size_t nrElements){
    for(int i = 0; i<nrElements;i++){
        if(arr1[i] != arr2[i]){
            return true;
        }
    }

    TEST_FAIL_MESSAGE("Arrays are equal");
}

mbedtls_pk_context getNonValidatedKey(RSACryptographer rsaCryptographer){

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

//Encryption and decryption works if you use one array for storing the encryption, and another for storing the decryption
void encrypt_decrypt(){
    unsigned char ENCRYPTION_OUTPUT_ARRAY[sizeof(OUTPUT_ARRAY)];

    operation_result = rsa_Cryptographer.encrypt(STR_TO_ENCRYPT,sizeof(STR_TO_ENCRYPT), ENCRYPTION_OUTPUT_ARRAY, sizeof(ENCRYPTION_OUTPUT_ARRAY), &oLen);

    if(!isGoodResult(operation_result)){
        TEST_FAIL_MESSAGE("ENCRYPTION FAILED");
    }

    operation_result = rsa_Cryptographer.decrypt(ENCRYPTION_OUTPUT_ARRAY,oLen,OUTPUT_ARRAY,sizeof(OUTPUT_ARRAY),&oLen);

    if(!isGoodResult(operation_result)){
        TEST_FAIL_MESSAGE("DECRYPTION FAILED");
    }

    TEST_ASSERT_EQUAL_STRING(STR_TO_ENCRYPT,OUTPUT_ARRAY);



}

//Encryption and decryption work if you use the same storing the encryption and decryption
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


//RSACryptographer.validate_key() = true <=> decrypt(encrypt(TEXT)) = TEXT
void validateIsTrueEncryptDecryptWorks(){
    TEST_ASSERT_EQUAL(RSABooleanTrue,rsa_Cryptographer.validate_key());

    operation_result = encryptDecrypt(rsa_Cryptographer);

    TEST_ASSERT_EQUAL(RSABooleanTrue,operation_result);
    TEST_ASSERT_EQUAL_STRING(STR_TO_ENCRYPT,OUTPUT_ARRAY);
}



//Worksn't, lol
void validateIsNotTrueEncryptDecryptWorksnt(){
    unsigned char examplePubKey[500];
    fill_char_unsignedString(examplePubKey,sizeof(examplePubKey),PEM_EMPTY_PLACEHOLDER); //For some reason, we have to fill it with empty placeholders

    auto * temporary_rsa_Cryptographer = new RSACryptographer();
    temporary_rsa_Cryptographer->generate_CTRX_context();
    temporary_rsa_Cryptographer->generate_key();

    TEST_ASSERT_EQUAL(RSABooleanTrue,temporary_rsa_Cryptographer->validate_key()); //Our key is valid

    mbedtls_pk_context temporary_pk_ctx = temporary_rsa_Cryptographer->get_RSA_context();

    mbedtls_pk_write_pubkey_pem(&temporary_pk_ctx,examplePubKey,sizeof(examplePubKey));
    mbedtls_pk_free(&temporary_pk_ctx);

    operation_result = mbedtls_pk_parse_public_key(&temporary_pk_ctx,(const unsigned char *) examplePubKey, sizeof(examplePubKey));

    if(!isGoodResult(operation_result)){
        TEST_FAIL_MESSAGE("COULD NOT PARSE PUBLIC KEY");
    }

    TEST_ASSERT_NOT_EQUAL(RSABooleanTrue,temporary_rsa_Cryptographer->validate_key()); //It is no longer valid :D
    operation_result = encryptDecrypt(*temporary_rsa_Cryptographer);

    TEST_ASSERT_EQUAL(MBEDTLS_ERR_PK_PASSWORD_MISMATCH,operation_result); //The error code, when the given private key doesn't allow for correct decryption

    for(int i = 0; i<sizeof(STR_TO_ENCRYPT);i++){
        TEST_ASSERT_NOT_EQUAL(STR_TO_ENCRYPT[i],OUTPUT_ARRAY[i]);
    }
}

//Generating new keys makes them valid
void newGeneratedKeysAreValid(){
    auto * temporary_rsa_Cryptographer = new RSACryptographer();
    temporary_rsa_Cryptographer->generate_CTRX_context();
    temporary_rsa_Cryptographer->generate_key();
    TEST_ASSERT_EQUAL(RSABooleanTrue,temporary_rsa_Cryptographer->validate_key());
    delete temporary_rsa_Cryptographer;
}

void newKeyIsUnique(){

    unsigned char *priv1, *priv2, *pub1, *pub2;
    priv1 = (unsigned char *) malloc(PEMPrivKeyLen * sizeof(unsigned char));
    priv2 = (unsigned char *) malloc(PEMPrivKeyLen * sizeof(unsigned char));
    pub1 = (unsigned char *) malloc(PEMPublicKeyLen * sizeof(unsigned char));
    pub2 = (unsigned char *) malloc(PEMPublicKeyLen * sizeof(unsigned char));

    fill_char_unsignedString(priv1,PEMPrivKeyLen,PEM_EMPTY_PLACEHOLDER);
    fill_char_unsignedString(priv2,PEMPrivKeyLen,PEM_EMPTY_PLACEHOLDER);
    fill_char_unsignedString(pub1,PEMPublicKeyLen,PEM_EMPTY_PLACEHOLDER);
    fill_char_unsignedString(pub2,PEMPublicKeyLen,PEM_EMPTY_PLACEHOLDER);

    //TODO: Vi får null pointers
    auto * temporary_rsa_Cryptographer = new RSACryptographer();
    temporary_rsa_Cryptographer->generate_CTRX_context();
    temporary_rsa_Cryptographer->generate_key();

    mbedtls_pk_context  rsa_ctx1 = temporary_rsa_Cryptographer->get_RSA_context();

    assert(temporary_rsa_Cryptographer->validate_key() == RSABooleanTrue);
    assert(mbedtls_pk_check_pair(&rsa_ctx1,&rsa_ctx1) == RSABooleanTrue);

    //Fill 1keys
    operation_result = mbedtls_pk_write_key_pem(&rsa_ctx1,priv1,PEMPrivKeyLen);

    if(!isGoodResult(operation_result)){
        Serial.println(-operation_result,HEX);
        Serial.print("COULD NOT GENERATE PRIVATE KEY 1 PEM FILE\n");
    }

    operation_result = mbedtls_pk_write_pubkey_pem(&rsa_ctx1,pub1,PEMPublicKeyLen);
    if(!isGoodResult(operation_result)){
        Serial.println(-operation_result,HEX);
        Serial.print("COULD NOT GENERATE PUBLIC KEY 1 PEM FILE\n");
    }

    temporary_rsa_Cryptographer->generate_key();

    assert(RSABooleanTrue == temporary_rsa_Cryptographer->validate_key());
    mbedtls_pk_context  rsa_ctx2 = temporary_rsa_Cryptographer->get_RSA_context();

    //Fill 2keys
    operation_result = mbedtls_pk_write_key_pem(&rsa_ctx2,priv2,PEMPrivKeyLen);
    if(!isGoodResult(operation_result)){
        Serial.println(-operation_result,HEX);
        Serial.print("COULD NOT GENERATE PRIVATE KEY 2 PEM FILE\n");
    }

    operation_result = mbedtls_pk_write_pubkey_pem(&rsa_ctx2,pub2,PEMPublicKeyLen);
    if(!isGoodResult(operation_result)){
        Serial.println(-operation_result,HEX);
        Serial.print("COULD NOT GENERATE PUBLIC KEY 2 PEM FILE\n");
    }

    println_unsignedString(pub1,PEMPublicKeyLen,CHR);
    println_unsignedString(pub2,PEMPublicKeyLen,CHR);
    assert(assertNotEqualArray(priv1, priv2, PEMPrivKeyLen) == true);
    assert(assertNotEqualArray(pub1, pub2, PEMPublicKeyLen) == true);
    free(priv1);
    free(priv2);
    free(pub1);
    free(pub2);
}



void setup()
{
    delay(5000); // service delay


    //DON'T PUT ANYTHING BEFORE THIS EXCEPT FOR DELAY!!!!
    UNITY_BEGIN(); //Define stuff after this
    rsa_Cryptographer.generate_CTRX_context();
    rsa_Cryptographer.generate_key();
    /*RUN_TEST(inputIsBiggerThanMaxInput);
    RUN_TEST(inputIsSameSizeAsMaxInput);
    RUN_TEST(outLenIsBiggerThanOutputArray);
    RUN_TEST(encrypt_decrypt);
    RUN_TEST(encrypt_decryptInPlace);
    RUN_TEST(validateIsTrueEncryptDecryptWorks);
    RUN_TEST(validateIsNotTrueEncryptDecryptWorksnt);*/
    RUN_TEST(newKeyIsUnique);
    RUN_TEST(newGeneratedKeysAreValid);
    UNITY_END(); // stop unit testing
}

void loop()
{
}