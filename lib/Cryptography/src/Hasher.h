//
// Created by DripTooHard on 01-06-2023.
//

#ifndef FAGPROJEKTLORA2023_HASHER_H
#define FAGPROJEKTLORA2023_HASHER_H

#include <Arduino.h>
#include <stdexcept>
#include "stdio.h"
#include "mbedtls/sha256.h"
#include "CryptographicSettings.h"

class Hasher{
public:
    virtual int  generate_checksum(unsigned char *input, size_t strLen, unsigned char *outputBuffer);
};

class SHA256Hasher:Hasher{

private:
    mbedtls_sha256_context SHA_ctx;
    esp_mbedtls_sha256_mode sha_256_mode = ESP_MBEDTLS_SHA256_HARDWARE;
    bool is_initialized;

public:
    SHA256Hasher();

    //Initializes the context, such that it is ready to calculate a hash
    int init_ctx();

    //Generates the checksum of the input and saves it to the outputBuffer
    int generate_checksum(unsigned char *input, size_t strLen, unsigned char *outputBuffer);
};
#endif //FAGPROJEKTLORA2023_HASHER_H
