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
        else
        {
            res =  mbedtls_pk_decrypt(&this->RSA_priv_ctx, inputArray,inputLen, outputArray, outLen, outSize ,mbedtls_ctr_drbg_random,&this->CTR_ctx);
        }

        //If our output is larger than the array
        if(*outLen>outSize)
        {
            log_e("ERROR: Output length exceeds size of the outputArray\n Output length: %i, output array size: %i",*outLen,outSize);
            throw std::logic_error("OUTPUT LENGTH EXCEEDS SIZE OF THE OUTPUT ARRAY");
        }

        return res;

    }

    mbedtls_pk_context get_public_context(){
        return this->RSA_pub_ctx;
    }

    mbedtls_pk_context get_private_context(){
        return this->RSA_priv_ctx;
    }

    int get_pub_key_pem(unsigned char ** buf){
        int result;

        unsigned char * temp;
        create_PEM_arr(&temp,PEMPubKeyLen);

        result = mbedtls_pk_write_pubkey_pem(&this->RSA_pub_ctx, temp, PEMPubKeyLen);

        if(!isGoodResult(result)){
            log_e("COULD NOT RETREIVE THE PUBLIC KEY'S PEM FILE. ERROR CODE:%x",-result);
            throw std::logic_error("UNABLE TO GET PUBLIC KEY'S PEM FILE");
            return result;
        }

        *buf = temp;
        return result;
    }

    int get_priv_key_pem(unsigned char ** buf){
        int result;

        unsigned char * temp;


        //We initialize the array - ensuring nothing else is written on it
        create_PEM_arr(&temp,PEMPrivKeyLen);

        result = mbedtls_pk_write_key_pem(&this->RSA_priv_ctx, temp, PEMPrivKeyLen);

        if(!isGoodResult(result)){
            log_e("FAILED TO GET PRIVATE KEY'S PEM FILE. ERROR CODE: %x",-result);
           throw std::logic_error("FAILED TO GET PRIVATE KEY'S PEM FILE");
        }

        *buf = temp;
        return result;
    }

    int parse_priv_key(unsigned char * key_pem, size_t keyLen){
        if(!&RSA_priv_ctx){
            mbedtls_pk_free(&RSA_priv_ctx);
        }

        mbedtls_pk_init(&RSA_priv_ctx);

        return mbedtls_pk_parse_key(&this->RSA_priv_ctx,key_pem,keyLen,NULL,0);
    }

    int parse_pub_key(unsigned char * key_pem, size_t keylen){
        if(!&RSA_pub_ctx){
            mbedtls_pk_free(&RSA_pub_ctx);
        }
        mbedtls_pk_init(&RSA_pub_ctx);

        return mbedtls_pk_parse_public_key(&this->RSA_pub_ctx,key_pem,keylen);
    }

    RSAPEMHandler * rsapem_handler = new RSAPEMHandler();

public:

    RSACryptographer()
    {

    }
    ~RSACryptographer(
            ){}




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
            log_e("ERROR: INPUT EXCEEDS MAX ENCRYPTION INPUT LEN %i",RSA_MAX_INPUT_LEN);
            throw std::logic_error("INPUT EXCEEDS MAX ENCRYPTION INPUT LEN");
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


        //TODO: Turn this into a single function...?
        log_i("Initializing key context...");

        if (ret == MBEDTLS_ERR_PK_BAD_INPUT_DATA)
        {
            log_e("Failed to setup pk context in generate_key, returned error BAD INPUT DATA");
            throw std::logic_error("Could not setup pk context");
        }
        else if(ret == MBEDTLS_ERR_PK_ALLOC_FAILED)
        {
            log_e("Failed to setup pk context in generate_key, returned error ALLOCATION FAILED");
            throw std::logic_error("Could not setup pk context");
        }


        log_i("Generating the private key...");
        ret = mbedtls_rsa_gen_key(mbedtls_pk_rsa(RSA_ctx), mbedtls_ctr_drbg_random, &CTR_ctx, pubKeyLen, RSAPubKeyEXPONENT);
        if (ret != RSABooleanTrue)
        {
            log_e("mbedtls_rsa_gen_key returned %x", -ret);
            throw std::logic_error("Could not generate key for pk context");
        }

        //Get PEMfiles in buffers and parse these into their respective keys
        unsigned char * PEMpub, * PEMpriv;
        log_i("GETTING THE PEM FILES FOR EACH KEY");
        create_PEM_arr(&PEMpub,PEMPubKeyLen);
        create_PEM_arr(&PEMpriv,PEMPrivKeyLen);

        //We can't use get_key_pem here, as the two keys aren't initialized.
        assert(isGoodResult(mbedtls_pk_write_pubkey_pem(&RSA_ctx,PEMpub,PEMPubKeyLen))); //<- CANNOT F' UP OR THE WHOLE DAMN THING WON'T WORK BUDDY WUDDY
        assert(isGoodResult(mbedtls_pk_write_key_pem(&RSA_ctx,PEMpriv,PEMPrivKeyLen))); //^- ...Which is why we have asserts here.

        log_i("PARSING PEM FILES");

        parse_key_pem(PEMpub, 0);
        parse_key_pem(PEMpriv, 1);

        //We malloc'ed the array, so we of course need to delete it afterwards to avoid memory leak :)
        free (PEMpriv);
        free (PEMpub);

        log_i("SUCCESFULLY GENERATED KEYS");

        return RSABooleanTrue;
    }

    int validate_key(){
        return mbedtls_pk_check_pair(&this->RSA_pub_ctx,&this->RSA_priv_ctx);
    }

    int validate_key(mbedtls_pk_context pub,mbedtls_pk_context priv){
        return mbedtls_pk_check_pair(&pub,&priv);
    }

    mbedtls_pk_context get_context(bool isPrivate){
        if(isPrivate)
        {
            return get_private_context();
        }
        else
        {
            return get_public_context();
        }
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
            result = get_priv_key_pem(buf);
        }else{
            result = get_pub_key_pem(buf);
        }

        //error
        if(!isGoodResult(result)){
            log_e("%x",-result);
            throw std::logic_error("COULD NOT GET KEY PEM");
        }

        return result;


    }

    int parse_key_pem(unsigned char * key_pem, bool isPrivateKeyPem){
        int operation_result;

        if(isPrivateKeyPem){
            operation_result = parse_priv_key(key_pem, PEMPrivKeyLen);
        }
        else{
            operation_result = parse_pub_key(key_pem, PEMPubKeyLen);
        }

        //Error
        if(!isGoodResult(operation_result)){
            log_e("%x",-operation_result);
            throw std::logic_error("COULD NOT PARSE KEY");
        }

        return RSABooleanTrue;

    }

    int parse_key_pem(unsigned char * key_pem, bool isPrivateKeyPem, size_t PEMLen){
        int operation_result;

        if(isPrivateKeyPem){
            operation_result = parse_priv_key(key_pem, PEMLen);
        }
        else{
            operation_result = parse_pub_key(key_pem, PEMLen);
        }

        //Error
        if(!isGoodResult(operation_result)){
            log_e("FAILED TO LOAD KEY PEM WITH ERROR: %x",-operation_result);
            throw std::logic_error("COULD NOT PARSE KEY");
        }

        return RSABooleanTrue;

    }


};