//
// Created by DripTooHard on 01-06-2023.
//

#include "Hasher.h"

SHA256Hasher::SHA256Hasher(){
    init_ctx();
}


/**
 *
 * @return 0 if no errors are encountered else the specific error code
 * @warning Please note, that mbedtls_sha256_init doesn't return any error warnings
 * @pre SHA_ctx != NULL
 * @post is_initialized is equal to 1
 *
 */
int SHA256Hasher::init_ctx() {

    if(&SHA_ctx == NULL){
        Serial.println(SHA256_ERR_CTX_IS_NULL);
        throw std::invalid_argument("COULD NOT INIT SHA256 CTX: CTX IS EQUAL TO NULL");
    }

    mbedtls_sha256_init(&SHA_ctx);
    is_initialized = 1;
    return 0;
}

/**
 *
 * \post is_initialized is equal to 0
 *
 * \param unsignedString The target we wish to hash
 * \param strlen    The length of the target
 * \param outputBuffer The buffer in which we put the hash. Must be at least 256 bits wide.
 *
 * \return         0 on success of everything but the initialization of the context else a specific error code
 * \warning        0
 */
int SHA256Hasher::generate_checksum(unsigned char *input, size_t strLen, unsigned char *outputBuffer){
    int res;

    if(!is_initialized){

        //init throws its own error
        init_ctx();
    }

    //Starts a calculation
    res = mbedtls_sha256_starts_ret(&SHA_ctx,0);
    if(!isGoodResult(res)){
        Serial.println(-res,HEX);
        throw std::runtime_error("COULD NOT START SHA256 CHECKSUM CALCULATION");
    }

    //Update context
    res = mbedtls_sha256_update_ret(&SHA_ctx,(const unsigned char *) input,strLen);
    if(!isGoodResult(res))
    {
        Serial.println(-res,HEX);
        throw std::runtime_error("COULD NOT START SHA256 CHECKSUM CALCULATION");
    }

    //Finish and store to output
    res = mbedtls_sha256_finish_ret(&SHA_ctx,outputBuffer);
    if(!isGoodResult(res)){
        Serial.println(-res,HEX);
        throw std::runtime_error("FAILED TO FINISH CHECKSUM CALCULATIONS");
    }

    //When you finish the calculations you have to re-init in order to make a new calculation
    is_initialized = 0;
    return res;


}