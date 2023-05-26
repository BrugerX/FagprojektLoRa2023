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
    mbedtls_pk_context RSA_pub_ctx;
    mbedtls_pk_context RSA_priv_ctx;
private:

    int get_pub_key_pem(unsigned char ** buf){
        int result;

        unsigned char * temp = (unsigned char *) malloc(PEMPubKeyLen * sizeof(unsigned char));
        result = mbedtls_pk_write_pubkey_pem(&this->RSA_pub_ctx, temp, PEMPubKeyLen);

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
        result = mbedtls_pk_write_key_pem(&this->RSA_priv_ctx, temp, PEMPrivKeyLen);

        if(!isGoodResult(result)){
            // TODO: Better exceptions
            // throw "FAILED TO WRITE PUBLIC KEY TO PEM FILE";
            Serial.print(-result,HEX);
        }

        *buf = temp;
        return result;
    }

    int load_priv_key(unsigned char * key_pem){
        if(!&RSA_priv_ctx){
            mbedtls_pk_free(&RSA_priv_ctx);
        }

        mbedtls_pk_init(&RSA_priv_ctx);

        return mbedtls_pk_parse_key(&this->RSA_priv_ctx,key_pem,PEMPrivKeyLen,NULL,0);
    }

    int load_pub_key(unsigned char * key_pem){
        if(!&RSA_pub_ctx){
            mbedtls_pk_free(&RSA_pub_ctx);
        }
        mbedtls_pk_init(&RSA_pub_ctx);

        return mbedtls_pk_parse_public_key(&this->RSA_pub_ctx,key_pem,PEMPubKeyLen);
    }

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
            res = mbedtls_pk_encrypt(&this->RSA_pub_ctx, inputArray, inputLen,  outputArray, outLen,
                                     outSize, mbedtls_ctr_drbg_random, &this->CTR_ctx);
        }
        else{
            res =  mbedtls_pk_decrypt(&this->RSA_priv_ctx, inputArray,inputLen, outputArray, outLen, outSize ,mbedtls_ctr_drbg_random,&this->CTR_ctx);
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
     * @post RSA_ctx.initialized == True, RSA_ctx.can_debug == True
     *
     */
    int generate_key(){
        mbedtls_pk_context RSA_ctx;

        //If the key has already been initialized we need to reset it.
        if(!&RSA_pub_ctx || !&RSA_priv_ctx){
            mbedtls_pk_free(&RSA_pub_ctx);
            mbedtls_pk_free(&RSA_priv_ctx);
        }

        mbedtls_pk_init(&RSA_ctx);
        mbedtls_pk_init(&RSA_pub_ctx);
        mbedtls_pk_init(&RSA_priv_ctx);

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

        //TODO: Turn this into a single function...?
        //Get PEMfiles in buffers and parse these into their respective keys
        unsigned char * PEMpub, * PEMpriv;
        Serial.println("GETTING THE PEM FILES FOR EACH KEY");
        PEMpub = (unsigned char * ) malloc(PEMPubKeyLen*sizeof(unsigned char));
        PEMpriv = (unsigned char * ) malloc(PEMPrivKeyLen*sizeof(unsigned char));

        assert(isGoodResult(mbedtls_pk_write_pubkey_pem(&RSA_ctx,PEMpub,PEMPubKeyLen)));
        assert(isGoodResult(mbedtls_pk_write_key_pem(&RSA_ctx,PEMpriv,PEMPrivKeyLen)));

        Serial.println("PARSING PEM FILES");

        ret = mbedtls_pk_parse_public_key(&RSA_pub_ctx,PEMpub,PEMPubKeyLen);
        if(ret != RSABooleanTrue){
            printf("%x",-ret);
            assert(false);
        }

        ret = mbedtls_pk_parse_key(&RSA_priv_ctx,PEMpriv,PEMPrivKeyLen,NULL,0);

        if(ret != RSABooleanTrue){
            printf("%x",-ret);
            assert(false);
        }

        //We malloc'ed the array, so we of course need to delete it afterwards to avoid memory leak ;)
        free (PEMpriv);
        free (PEMpub);

        Serial.println("SUCCESFULLY GENERATED KEYS");

        return RSABooleanTrue;
    }

    int validate_key(){
        return mbedtls_pk_check_pair(&this->RSA_pub_ctx,&this->RSA_priv_ctx);
    }

    int validate_key(mbedtls_pk_context pub,mbedtls_pk_context priv){
        return mbedtls_pk_check_pair(&pub,&priv);
    }

    mbedtls_pk_context get_public_context(){
        return this->RSA_pub_ctx;
    }

    mbedtls_pk_context get_private_context(){
        return this->RSA_priv_ctx;
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

    int load_key_pem(unsigned char * key_pem, bool isPrivateKeyPem){
        int operation_result;

        if(isPrivateKeyPem){
            operation_result = load_priv_key(key_pem);
        }
        else{
            operation_result = load_pub_key(key_pem);
        }

        //Error
        if(!isGoodResult(operation_result)){
            Serial.println(-operation_result,HEX);
            throw std::runtime_error("COULD NOT PARSE KEY");
        }

        return RSABooleanTrue;

    }


};