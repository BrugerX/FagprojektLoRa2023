//
// Created by DripTooHard on 03-04-2023.
//

#include "RSAEncryption.h"



/**
 *                 Depreciated version of calculating the Sha256 hash and storing it in an output buffer.
 *                 We use sha_parallel_engine instead, as it uses the ESP32's hardware accelerator.
 *
 * \param unsignedString The target we wish to hash
 * \param strlen    The length of the target
 * \param outputBuffer The buffer in which we put the hash. Must be at least 256 bits wide.
 *
 * \return         \c 0 on failure.
 * \return         \c 1 on success.
 */
 /*
int generateSha256Hash(unsigned char * unsignedString, int strLen ,unsigned char * outputBuffer){
    mbedtls_sha256_context ctx;
    ctx.mode = ESP_MBEDTLS_SHA256_HARDWARE; //We use the hardware accelerator

    //Init context
    mbedtls_sha256_init(&ctx);

    //Starts a calculation
    if(mbedtls_sha256_starts_ret(&ctx,0)){
        return 0;
    }

    //Update context
    if(mbedtls_sha256_update_ret(&ctx,(const unsigned char *) unsignedString,strLen)){
        return 0;
    }

    //Finish and store to output
    mbedtls_sha256_finish(&ctx,outputBuffer);

    //Free context
    mbedtls_sha256_free(&ctx);
}
*/

 /**
  *
  * Compares string1[0:string1_size] with string2[0:string2_size]
  * Returns RSABooleanTrue if they containt the exact same elemnts and are of the exact same size
  * Returns RSABooleanFalse otherwise
  *
  * Used for validating hashes.
  *
  * @param hash1
  * @param hash1_size
  * @param hash2
  * @param hash2_size
  * @return RSABoolean true or false, depending on whether the two hashes are the same
  */
 int is_same_unsigned_string(unsigned char * string1, size_t string1_size ,unsigned char * string2, size_t string2_size){

     //If the suppossed hash is not the same size as the actual hash
     if(string1_size != string2_size){
         return RSABooleanFalse;
     }

     //We then compare the two hashes
     for(int i = 0; i<string1_size;i++){
         if(string1[i] != string2[i]){
             return RSABooleanFalse;
         }
     }

     return RSABooleanTrue;
 }

/**
 * @desc Gets the CTR DRBG context needed for the random mbed CTR-DRBG random number generator ready for use
 *
 * @param ctr_drbg: The context that we need to get ready for use
 *
 * @return 0 on sucess, 1 else
 * */
int getready_CTRDRBG_context(mbedtls_ctr_drbg_context * ctr_drbg){
    mbedtls_entropy_context entropy; //Used to seed the drbg

    mbedtls_ctr_drbg_init(ctr_drbg);
    mbedtls_entropy_init(&entropy);

    Serial.println(TAG);
    Serial.println("Seeding the random number generator...");
    int ret = (mbedtls_ctr_drbg_seed(ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0)) != 0;
    if (ret)
    {
        Serial.print("Error in seeding the random number generator\nmbedtls_ctr_drbg_seed returned: ");
        Serial.print(ret);
        return RSABooleanFalse;
        //ESP_LOGE(TAG, "mbedtls_ctr_drbg_seed returned %d", ret);
    }

    return 0;
};


/**
 * Generates the PK context with both public and private keys instantiated.
 *
 *  \param ctr_drbg: The initialized and seeded ctr_drbg context for the ctr_drbg random number generator used to generate the keys
 *  \param key: The pk context we need to generate keys for
 *
 */
int generate_keys_PK_context(mbedtls_pk_context * key, mbedtls_ctr_drbg_context * ctr_drbg){
    mbedtls_rsa_context rsa_cntx;

    mbedtls_pk_init(key);


    int ret = mbedtls_pk_setup(key, mbedtls_pk_info_from_type(MBEDTLS_PK_RSA));
    ESP_LOGI(TAG_MAIN, "Initializing key context...");
    if (ret != 0)
    {
        ESP_LOGE(TAG_WORDS, "mbedtls_pk_info_from_type returned %d", ret);
        return RSABooleanFalse;
    }

    ESP_LOGI(TAG, "Generating the private key...");
    ret = mbedtls_rsa_gen_key(mbedtls_pk_rsa(*key), mbedtls_ctr_drbg_random, ctr_drbg, pubKeyLen, RSAPubKeyEXPONENT);
    if (ret != 0)
    {
        ESP_LOGE(TAG_WORDS, "mbedtls_rsa_gen_key returned %d", ret);
        return RSABooleanFalse;
    }

    return 0;

}


/**
 *  \desc Takes a plain text input, the size of the input and its suppossed SHA2_256 hash
 *  and verifies if the hash indeed is the hash of the plain text.
 *
 *  \param plainText The plaintext of the hash
 *  \param plaintext_len The length of the plaintext
 *  \param hash The SHA256 hash of the plaintext, an unsigned char string of size 32
 *
 *
 *  \returns
 *  \return BooleanFalse: If the actual hash of the plaintext contains a char, which the suppossed hash doesn't contain
 *  \return BooleanTrue: Otherwise
 */
int verify_ptxt_SHA256hash(const unsigned char * plainText, size_t plaintext_len, unsigned char * suppossed_hash, size_t hashSize){
    unsigned char outputBuffer[SHA256_OUTPUT_BUFFERLEN];
    esp_sha(SHA2_256,  plainText,  plaintext_len,outputBuffer);
    return is_same_unsigned_string(outputBuffer,SHA256_OUTPUT_BUFFERLEN,suppossed_hash,hashSize);

}


