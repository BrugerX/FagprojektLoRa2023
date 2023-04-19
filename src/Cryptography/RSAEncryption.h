//
// Created by DripTooHard on 03-04-2023.
//

#ifndef UNTITLED1_KEYGENERATION_H


#define UNTITLED1_KEYGENERATION_H

#include "Arduino.h"
#include "CryptographicSettings.cpp"
#include "mbedtls/rsa.h"
#include "mbedtls/entropy.h"
#include "mbedtls/pk.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/sha256.h"
#include "sha/sha_parallel_engine.h"




static const char* TAG = "RSACryptography";


/*Generates the CTR DRBG context needed for the random mbed CTR-DRBG random number generator
 *
 *
 * */
int getready_CTRDRBG_context(mbedtls_ctr_drbg_context * ctr_drbg);


/**
 * Generates the PK context with both public and private keys instantiated.
 *
 *  \param ctr_drbg: The initialized and seeded ctr_drbg context for the ctr_drbg random number generator used to generate the keys
 *
 */
int generate_keys_PK_context(mbedtls_pk_context * key,mbedtls_ctr_drbg_context * ctr_drbg);

/**
 *  \desc Takes a plain text input, the size of the input and its suppossed SHA2_256 hash and verifies if the hash indeed is the hash of the plain text.
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
int verify_ptxt_SHA256hash(const unsigned char * plainText, size_t plaintext_len, unsigned char * suppossed_hash, size_t hashSize);


#endif //UNTITLED1_KEYGENERATION_H
