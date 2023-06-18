//
// Created by DripTooHard on 14-05-2023.
//

#include <Arduino.h>
#include <unity.h>
#include "UnsignedStringUtility.cpp"
#include <CryptographicSettings.cpp>
#include <Cryptographer.cpp>
#include <TestUtility.h>


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

    TEST_ASSERT_TRUE_MESSAGE(assertNotEqualArray(STR_TO_ENCRYPT,OUTPUT_ARRAY,sizeof(STR_TO_ENCRYPT)),"Arrays are equal");

    operation_result = rsaCrypto.decrypt(OUTPUT_ARRAY,oLen,OUTPUT_ARRAY,sizeof(OUTPUT_ARRAY),&oLen);

    if(!isGoodResult(operation_result)){
        return operation_result;
    }

    return RSABooleanTrue;

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
    try{
    operation_result = rsa_Cryptographer.encrypt(INPUT_ARR, sizeof(INPUT_ARR), OUTPUT_ARRAY, sizeof(OUTPUT_ARRAY), &oLen);
        TEST_FAIL_MESSAGE("DIDN'T RECEIVE AN ERROR WHEN EXCEEDING THE MAX INPUT LEN");
    }
    catch(std::logic_error){}

};

void inputIsSameSizeAsMaxInput(){
    unsigned char INPUT_ARR[RSA_MAX_INPUT_LEN];
    operation_result = rsa_Cryptographer.encrypt(INPUT_ARR, sizeof(INPUT_ARR), OUTPUT_ARRAY, sizeof(OUTPUT_ARRAY), &oLen);
    TEST_ASSERT_EQUAL(RSABooleanTrue,operation_result);
}

//The output length is too big for the RSA algorithm
void outLenIsBiggerThanOutputArray(){
    unsigned char TEST_OUT[1];
    try{
        rsa_Cryptographer.encrypt(STR_TO_ENCRYPT,sizeof(STR_TO_ENCRYPT), TEST_OUT, sizeof(TEST_OUT)/sizeof(TEST_OUT[0]), &oLen);
        TEST_ASSERT_TRUE(oLen >= sizeof(TEST_OUT)/sizeof(TEST_OUT[0]));
        TEST_FAIL_MESSAGE("DID NOT RECEIVE AN ERROR WHEN THE OUTPUT ARRAY SIZE WAS SMALLER THAN THE OUTPUT SIZE");
    }
    catch (std::logic_error)
    {

    }
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



//Generating new keys makes them valid
void newGeneratedKeysAreValid(){
    auto * temporary_rsa_Cryptographer = new RSACryptographer();
    temporary_rsa_Cryptographer->generate_CTRX_context();
    temporary_rsa_Cryptographer->generate_key();
    temporary_rsa_Cryptographer->generate_key();
    TEST_ASSERT_EQUAL(RSABooleanTrue,temporary_rsa_Cryptographer->validate_key());
    delete temporary_rsa_Cryptographer;
}

//RSACryptographer.validate_key() = true <=> decrypt(encrypt(TEXT)) = TEXT
void validateIsTrueEncryptDecryptWorks(){
    TEST_ASSERT_EQUAL(RSABooleanTrue,rsa_Cryptographer.validate_key());

    operation_result = encryptDecrypt(rsa_Cryptographer);

    TEST_ASSERT_EQUAL(RSABooleanTrue,operation_result);
    TEST_ASSERT_EQUAL_STRING(STR_TO_ENCRYPT,OUTPUT_ARRAY);
}

//Worksn't, lol
/*
 */
void validateIsNotTrueEncryptDecryptWorksnt(){
    //The private and public keys
    unsigned char *pub;

    auto * temporary_rsa_Cryptographer = new RSACryptographer();
    temporary_rsa_Cryptographer->generate_CTRX_context();
    temporary_rsa_Cryptographer->generate_key();

    TEST_ASSERT_EQUAL(RSABooleanTrue,temporary_rsa_Cryptographer->validate_key()); //Our key is valid

    //The public key will be from the first context
    operation_result = temporary_rsa_Cryptographer->get_key_pem(&pub,0);

    if(!isGoodResult(operation_result)){
        log_e("%x",-operation_result);
        TEST_FAIL_MESSAGE("COULD NOT GET PUBLIC KEY PEM FILE");
    }

    //We first get a public key, which we will use to show, that the validation doesn't turn out to be true
    mbedtls_pk_context pub_ctx;
    mbedtls_pk_init(&pub_ctx);
    operation_result = mbedtls_pk_parse_public_key(&pub_ctx,pub,PEMPubKeyLen);

    if(!isGoodResult(operation_result)){
        Serial.print(-operation_result,HEX);
        TEST_FAIL_MESSAGE("COULD NOT PARSE PUBLIC KEY PEM");
    }

    //We encrypt the input
    temporary_rsa_Cryptographer->encrypt(STR_TO_ENCRYPT,sizeof(STR_TO_ENCRYPT),OUTPUT_ARRAY,sizeof(OUTPUT_ARRAY),&oLen);

    //We now fill out the private key with a second context
    temporary_rsa_Cryptographer->generate_key();

    mbedtls_pk_context priv_ctx = temporary_rsa_Cryptographer->get_context(1);

    TEST_ASSERT_EQUAL(RSABooleanTrue,temporary_rsa_Cryptographer->validate_key());

    //We use the public key to encrypt
    temporary_rsa_Cryptographer->decrypt(OUTPUT_ARRAY,oLen,OUTPUT_ARRAY,sizeof(OUTPUT_ARRAY),&oLen);


    TEST_ASSERT_FALSE(RSABooleanTrue == temporary_rsa_Cryptographer->validate_key(pub_ctx,priv_ctx));
    TEST_ASSERT_TRUE(assertNotEqualArray(OUTPUT_ARRAY,STR_TO_ENCRYPT,sizeof(STR_TO_ENCRYPT)));

    delete(temporary_rsa_Cryptographer);
    free(pub);
}


//Whenever we generate a new pair of keys, they're unique/not identical with the previous pair
void newKeyIsUnique(){

    unsigned char *priv1, *priv2, *pub1, *pub2;


    //Generate the first pair of keys
    auto * temporary_rsa_Cryptographer = new RSACryptographer();
    temporary_rsa_Cryptographer->generate_CTRX_context();
    temporary_rsa_Cryptographer->generate_key();

    //The key we got them from is valid
    TEST_ASSERT_EQUAL(RSABooleanTrue,temporary_rsa_Cryptographer->validate_key());

    //Get the public key 1
    operation_result = temporary_rsa_Cryptographer->get_key_pem(&pub1,0);

    if(!isGoodResult(operation_result)){
        Serial.print(-operation_result,HEX);
        TEST_FAIL_MESSAGE("UNABLE TO GET PUBLIC KEY 1 PEM\n");
    }

    //Get the private key 1
    operation_result = temporary_rsa_Cryptographer->get_key_pem(&priv1,1);

    if(!isGoodResult(operation_result)){
        Serial.print(-operation_result,HEX);
        TEST_FAIL_MESSAGE("UNABLE TO GET PRIVATE KEY 1 PEM\n");
    }

    //Generate a new pair of keys
    operation_result = temporary_rsa_Cryptographer->generate_key();
    if(!isGoodResult(operation_result)){
        Serial.print(-operation_result,HEX);
        TEST_FAIL_MESSAGE("UNABLE TO GENERATE NEW PAIR OF KEYS");
    }
    TEST_ASSERT_EQUAL(RSABooleanTrue,temporary_rsa_Cryptographer->validate_key());

    //Get the public key 2
    operation_result = temporary_rsa_Cryptographer->get_key_pem(&pub2,0);

    if(!isGoodResult(operation_result)){
        Serial.print(-operation_result,HEX);
        TEST_FAIL_MESSAGE("UNABLE TO GET PUBLIC 2 KEY PEM\n");
    }

    //Get the private key 2
    operation_result = temporary_rsa_Cryptographer->get_key_pem(&priv2,1);

    if(!isGoodResult(operation_result)){
        Serial.print(-operation_result,HEX);
        TEST_FAIL_MESSAGE("UNABLE TO GET PRIVATE 2 KEY PEM\n");
    }

    TEST_ASSERT_TRUE(assertNotEqualArray(priv1,priv2,PEMPrivKeyLen));
    TEST_ASSERT_TRUE(assertNotEqualArray(pub1, pub2, PEMPubKeyLen));

    free(priv1);
    free(priv2);
    free(pub1);
    free(pub2);
    delete(temporary_rsa_Cryptographer);
}

//If we get the PEM file for public- and private key they're valid together
void PEMFilesAreValid(){
    int operation_result;

    //Create a temporary RSA cryptographer

    auto * temporary_rsa_Cryptographer = new RSACryptographer();
    temporary_rsa_Cryptographer->generate_CTRX_context();
    temporary_rsa_Cryptographer->generate_key();


    assert(temporary_rsa_Cryptographer->validate_key() == RSABooleanTrue);

    //Filling the buffers with keys
    unsigned char * pub;
    unsigned char * priv;
    operation_result = temporary_rsa_Cryptographer->get_key_pem(&pub,0);
    if(!isGoodResult(operation_result)){
        Serial.print(-operation_result,HEX);
        TEST_FAIL_MESSAGE("UNABLE TO GET PUBLIC KEY PEM\n");
        println_unsignedString(pub, PEMPubKeyLen, CHR);
    }

    operation_result = temporary_rsa_Cryptographer->get_key_pem(&priv,1);

    if(!isGoodResult(operation_result)){
        Serial.print(-operation_result,HEX);
        TEST_FAIL_MESSAGE("UNABLE TO GET PRIVATE KEY PEM\n");
        println_unsignedString(priv,PEMPrivKeyLen,CHR);
    }

    //Parsing these keys into a context
    mbedtls_pk_context pk_ctx_pub;
    mbedtls_pk_context pk_ctx_priv;

    mbedtls_pk_init(&pk_ctx_pub);
    mbedtls_pk_init(&pk_ctx_priv);
    operation_result = mbedtls_pk_parse_public_key(&pk_ctx_pub, pub, PEMPubKeyLen);
    if(!isGoodResult(operation_result)){
        Serial.print(-operation_result,HEX);
        TEST_FAIL_MESSAGE("UNABLE TO PARSE PUBLIC KEY");
    }

    operation_result = mbedtls_pk_parse_key(&pk_ctx_priv,priv,PEMPrivKeyLen,NULL,69);
    if(!isGoodResult(operation_result)){
        Serial.print(-operation_result,HEX);
        TEST_FAIL_MESSAGE("UNABLE TO PARSE PRIVATE KEY");
    }

    //Asserting, that the keys match
    TEST_ASSERT_EQUAL(RSABooleanTrue,rsa_Cryptographer.validate_key(pk_ctx_pub,pk_ctx_priv));
    free(priv);
    free(pub);
    delete(temporary_rsa_Cryptographer);
}

/*
 * We check if loading new keys into an RSA_Cryptographer object works by loading a functional pair from RSACryptoA into RSACryptoB
 * Then we check to see if validate(RSACryptoA.pub,RSACryptoB.priv) == True && validate(RSACryptoB.pub,RSACryptoA.priv) == True
 */
void loadingNewKeysAreValid(){
    printf("GOT SO FAR");
    auto * temporary_rsa_cryptographer = new RSACryptographer();
    temporary_rsa_cryptographer->generate_CTRX_context();
    temporary_rsa_cryptographer->generate_key();
    TEST_ASSERT_EQUAL(RSABooleanTrue,temporary_rsa_cryptographer->validate_key());

    /*
     * We load the two keys from rsa_Cryptographer into the temporary RSA cryptographer
     */

    unsigned char * privPEM, * pubPEM;
    rsa_Cryptographer.get_key_pem(&pubPEM,0);
    rsa_Cryptographer.get_key_pem(&privPEM,1);

    temporary_rsa_cryptographer->parse_key_pem(pubPEM, 0);
    temporary_rsa_cryptographer->parse_key_pem(privPEM, 1);
    /*
     * We now check to see if their encryption is the same
     */

    operation_result = temporary_rsa_cryptographer->validate_key(temporary_rsa_cryptographer->get_context(0),rsa_Cryptographer.get_context(1));
    TEST_ASSERT_EQUAL(RSABooleanTrue,operation_result);

    operation_result = temporary_rsa_cryptographer->validate_key(rsa_Cryptographer.get_context(0),temporary_rsa_cryptographer->get_context(1));
    TEST_ASSERT_EQUAL(RSABooleanTrue,operation_result);

    free(privPEM);
    free(pubPEM);
    delete(temporary_rsa_cryptographer);
}


void automaticKeySizeDetection()
{}

void loadingSource()
{

}

void setup()
{
    delay(5000); // service delay


    //DON'T PUT ANYTHING BEFORE THIS EXCEPT FOR DELAY!!!!
    UNITY_BEGIN(); //Define stuff after this
    rsa_Cryptographer.generate_CTRX_context();
    rsa_Cryptographer.generate_key();
    RUN_TEST(inputIsBiggerThanMaxInput);
    RUN_TEST(inputIsSameSizeAsMaxInput);
    RUN_TEST(outLenIsBiggerThanOutputArray);
    RUN_TEST(encrypt_decrypt);
    RUN_TEST(encrypt_decryptInPlace);
    RUN_TEST(validateIsTrueEncryptDecryptWorks);
    RUN_TEST(validateIsNotTrueEncryptDecryptWorksnt);
    RUN_TEST(newKeyIsUnique);
    RUN_TEST(newGeneratedKeysAreValid);
    RUN_TEST(PEMFilesAreValid);
    RUN_TEST(loadingNewKeysAreValid);
    UNITY_END(); // stop unit testing
}

void loop()
{
}