//
// Created by DripTooHard on 15-04-2023.
//

#include "Cryptographer.h"

class Cryptographer{
protected:
    mbedtls_ctr_drbg_context CTR_ctx;

public:
    Cryptographer(){
        if(generate_CTRX_context() != 0){
            throw;
        }
    }

    virtual ~Cryptographer(){}

    //TODO: Add PEMformatter

    virtual int encrypt(unsigned char * inputArray, unsigned char * outputArray){}
    virtual int decrypt(unsigned char *, unsigned char*){}
    virtual int generate_key(){}
    virtual int validate_key(){}
    int generate_CTRX_context(){
        mbedtls_entropy_context entropy; //Used to seed the drbg

        mbedtls_ctr_drbg_init(&this->CTR_ctx);
        mbedtls_entropy_init(&entropy);

        Serial.println(TAG);
        Serial.println("Seeding the random number generator...");
        int ret = (mbedtls_ctr_drbg_seed(&this->CTR_ctx, mbedtls_entropy_func, &entropy, NULL, 0)) != 0;
        if (ret)
        {
            Serial.print("Error in seeding the random number generator\nmbedtls_ctr_drbg_seed returned: ");
            Serial.print(ret);
            return RSABooleanFalse;
            //ESP_LOGE(TAG, "mbedtls_ctr_drbg_seed returned %d", ret);
        }

        return 0;}

};

class RSACryptographer : public Cryptographer{

protected:
    mbedtls_pk_context RSA_ctx;

public:
    RSACryptographer(){}
    ~RSACryptographer(){}

    int encrypt(unsigned char * inputArray, size_t inputLen, unsigned char * outputArray, size_t * outLen){
        size_t outSize = sizeof(outputArray);

        //The input is larger than what our encryption algorithm can handle
        if(inputLen>RSA_MAX_INPUT_LEN);{
            Serial.print("ERROR: INPUT: \n");
            println_unsignedString(inputArray,inputLen,CHR);
            Serial.print("EXCEEDS MAX ENCRYPTION INPUT LEN: ");
            Serial.print(RSA_MAX_INPUT_LEN);
            return RSA_ERR_INPUT_EXCEEDS_MAX_LEN;
        }

        return mbedtls_pk_encrypt(&this->RSA_ctx,(const unsigned char *) inputArray,inputLen,(const unsigned char *) outputArray, outLen, outSize ,mbedtls_ctr_drbg_random,&this->CTR_ctx);

    }

};