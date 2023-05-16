//
// Created by DripTooHard on 15-04-2023.
//

#include "Cryptographer.h"

class Cryptographer{
protected:
    mbedtls_ctr_drbg_context CTR_ctx;

public:
    Cryptographer(){
    }

    virtual ~Cryptographer(){}

    //TODO: Add PEMformatter

    virtual int encrypt(unsigned char * inputArray, size_t inputLen, unsigned char * outputArray, size_t outSize, size_t * outLen) = 0;
    virtual int decrypt(unsigned char * inputArray, size_t inputLen, unsigned char * outputArray,size_t outSize, size_t * outLen) = 0;
    virtual int generate_key() = 0;
    virtual int validate_key() = 0;

    int generate_CTRX_context(){
        mbedtls_ctr_drbg_free(&CTR_ctx);
        mbedtls_entropy_context entropy; //Used to seed the drbg

        mbedtls_entropy_init(&entropy);
        mbedtls_ctr_drbg_init(&this->CTR_ctx);


        Serial.println("Seeding the random number generator...");
        int ret = (mbedtls_ctr_drbg_seed(&this->CTR_ctx, mbedtls_entropy_func, &entropy, NULL, 0)) != 0;
        if (ret)
        {
            Serial.print("Error in seeding the random number generator\nmbedtls_ctr_drbg_seed returned: ");
            Serial.print(ret);
            return RSABooleanFalse;
            //ESP_LOGE(TAG, "mbedtls_ctr_drbg_seed returned %d", ret);
        }

        return 0;
    };

    mbedtls_ctr_drbg_context get_CTRX_context(){
        return CTR_ctx;
    }

};

class RSACryptographer : public Cryptographer{

protected:
    mbedtls_pk_context RSA_ctx;

public:
    RSACryptographer()
    {

    }
    ~RSACryptographer(
            ){}


    /**
     *
     * @param inputArray : The array which we would like to do our encryption/decryption on
     * @param inputLen
     * @param outputArray
     * @param outLen : The length of the result (not the size of the outputArray)
     * @param isEncryption : 0 if we're decrypting, 1 if we're encrypting
     * @return 0 if succesfull, otherwise a specified error code
     */
    int use_key(unsigned char * inputArray, size_t inputLen, unsigned char * outputArray,size_t outSize, size_t * outLen, int isEncryption){
        int res;

        if(isEncryption) {
            res = mbedtls_pk_encrypt(&this->RSA_ctx, inputArray, inputLen,  outputArray, outLen,
                                     outSize, mbedtls_ctr_drbg_random, &this->CTR_ctx);
        }
        else{
            res =  mbedtls_pk_decrypt(&this->RSA_ctx, inputArray,inputLen, outputArray, outLen, outSize ,mbedtls_ctr_drbg_random,&this->CTR_ctx);
        }

        //If our output is larger than the array
        if(*outLen>outSize){ //2
            Serial.println("ERROR: Output length exceeds size of the outputArray");
            Serial.println(*outLen);
            Serial.println(outSize);
            return RSA_ERR_OUTPUT_EXCEEDS_OUTPUT_ARRAY_LEN;
        }

        return res;

    }

    /**
     * @pre inputLen <= |inputArray| && outputSize<=outputArray
     * @post outLen = |encrypted(inputArray)| && outputArray[0;outLen] = encrypted(inputArray)
     * @param inputArray
     * @param inputLen
     * @param outputArray
     * @param outSize
     * @param outLen
     * @return
     */
    int encrypt(unsigned char * inputArray, size_t inputLen, unsigned char * outputArray,size_t outSize, size_t * outLen){

        //The input is larger than what our encryption algorithm can handle
        if(inputLen>RSA_MAX_INPUT_LEN){ //1
            Serial.print("ERROR: INPUT: \n");
            println_unsignedString(inputArray,inputLen,CHR);
            Serial.print("EXCEEDS MAX ENCRYPTION INPUT LEN: ");
            Serial.print(RSA_MAX_INPUT_LEN);
            return RSA_ERR_INPUT_EXCEEDS_MAX_LEN;
        }


        return use_key(inputArray, inputLen, outputArray, outSize, outLen, 1);

    }

    int decrypt(unsigned char * inputArray, size_t inputLen, unsigned char * outputArray,size_t outSize, size_t * outLen) {

        return use_key(inputArray, inputLen, outputArray, outSize, outLen, 0);

    }

    /**
     * @pre &RSA_ctx != null && RSA_ctx.initialized == True
     * @post
     *
     */
    int generate_key(){
        if(!&RSA_ctx){
            free_key();
        }

        mbedtls_pk_init(&RSA_ctx);


        int ret = mbedtls_pk_setup(&RSA_ctx, mbedtls_pk_info_from_type(MBEDTLS_PK_RSA));
        Serial.println("Initializing key context...");
        ESP_LOGI(TAG_MAIN, "Initializing key context...");
        if (ret != RSABooleanTrue)
        {
            ESP_LOGE(TAG_WORDS, "mbedtls_pk_info_from_type returned %d", ret);
            return RSABooleanFalse;
        }

        Serial.println("Generating the private key...");
        ret = mbedtls_rsa_gen_key(mbedtls_pk_rsa(RSA_ctx), mbedtls_ctr_drbg_random, &CTR_ctx, pubKeyLen, RSAPubKeyEXPONENT);
        if (ret != RSABooleanTrue)
        {
            ESP_LOGE(TAG_WORDS, "mbedtls_rsa_gen_key returned %d", ret);
            return RSABooleanFalse;
        }

        return RSABooleanTrue;
    }

    int validate_key(){
        return mbedtls_pk_check_pair(&this->RSA_ctx,&this->RSA_ctx);
    }

    mbedtls_pk_context get_RSA_context(){
        return this->RSA_ctx;
    }

    int free_key(){
        mbedtls_pk_free(&RSA_ctx);
        return 0;
    }

    /**
     * @description Takes a pointer to an unsigned char and points it towards an unsigned char array containing (ONLY) the PEM file of the specified key
     *
     * @HEAP: THE ARRAY WILL BE STORED ON THE HEAP AND MUST THEREFORE BE MANUALLED FREED AFTERWARDS
     *
     * @Note: This method uses huge amounts of memory.
     *
     *        For public operation: |final_array| + |temp| >= ~800 + 1500 bytes
     *        For private operation: |final_array| + |temp| >= ~1500 + 1800 bytes
     *
     * @param buf: The buffer which will point towards the PEM file
     * @param getPrivateKey: Whether we want the private og public pem file
     * @return Returns 0 if everything went well else specific error code
     */
    int get_key_pem(unsigned char ** buf,bool getPrivateKey){
        int result;

        if(getPrivateKey) {
            return this->get_priv_key_pem(buf);
        }else{
            return this->get_pub_key_pem(buf);
        }


    }

    int get_pub_key_pem(unsigned char ** buf){
        int result;

        unsigned char * temp = (unsigned char *) malloc(PEMPublicKeyLen * sizeof(unsigned char));
        result = mbedtls_pk_write_pubkey_pem(&this->RSA_ctx,temp,PEMPublicKeyLen);

        if(!isGoodResult(result)){
            //TODO: Better exceptions
            //throw "FAILED TO WRITE PUBLIC KEY TO PEM FILE";
            Serial.print(-result,HEX);
        }

        *buf = temp;
        return result;
    }

    int get_priv_key_pem(unsigned char ** buf){
        int result;

        unsigned char * temp = (unsigned char *) malloc(PEMPrivKeyLen * sizeof(unsigned char));
        result = mbedtls_pk_write_key_pem(&this->RSA_ctx, temp, PEMPrivKeyLen);

        if(!isGoodResult(result)){
            // TODO: Better exceptions
            // throw "FAILED TO WRITE PUBLIC KEY TO PEM FILE";
            Serial.print(-result,HEX);
        }

        *buf = temp;
        return result;
    }

};