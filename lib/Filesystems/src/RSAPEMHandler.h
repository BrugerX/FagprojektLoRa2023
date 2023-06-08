//
// Created by DripTooHard on 04-06-2023.
//

#ifndef FAGPROJEKTLORA2023_RSAPEMHANDLER_H
#define FAGPROJEKTLORA2023_RSAPEMHANDLER_H

#include <RegexUtility.h>
#include <CryptographicSettings.h>

#define BAD_PEM_RESULT -1

bool isGoodPEMResult(int result);

/**
 *  The purpose of the RSAPEMHandler is responsible for extracting and modifying data regarding MbedTLS RSA PEM files
 */
class RSAPEMHandler{
    const char * regex_beginning_header_pattern = "-----BEGIN (PUBLIC|PRIVATE) KEY-----";
    const char * regex_ending_header_pattern = "-----END (PUBLIC|PRIVATE) KEY-----";
    const char * pub_beginning_header = "-----BEGIN PUBLIC KEY-----";
    const char * pub_ending_header = "-----END PUBLIC KEY-----\n";


private:
    size_t pub_beginning_header_size = 26;  //Size of the header minus the null terminating string

    size_t pub_ending_header_size = 26; //We include the null terminating string here, as it indicates the end of the PEM file

private:
    /**
     * Gets the beginning index of the source of the PEM file
     * That is, the PEM file minus the beginning header starts including that index
     */
    void get_begin_source_IDX(unsigned char *PEMFile, size_t PEMFile_len, int * idx);

    /**
     * Gets the end index of the source of the PEM file
     * That is, the PEM file minus the ending header ends including that index
     *
     * @param
     *       PEMFile [IN] The PEMFile for which we would like to get the end index of the source
     *       idx [OUT] The int which holds the index for char immediately before the first "-" in "-----END (PUBLIC|PRIAVTE) KEY-----"
     *
     */

    void get_end_source_IDX(unsigned char * PEMFile, size_t PEMFile_len, int * idx);

    void get_source_len(size_t PEMFile_original_len, int beginIDX, int endIDX, size_t * new_len);


    void add_public_begin_header(unsigned char * PEMFile);
    void add_public_end_header(unsigned char * PEMFile, size_t src_size);

    __attribute__((unused)) void addPrivateBeginHeader(unsigned char * PEMFile);

    __attribute__((unused)) void addPrivateEndHeader(unsigned char * PEMFile,size_t src_size);

    void add_src(unsigned char *PEMFile, size_t src_size, unsigned char * source);


public:
    /**
     * @pre The PEM file in PEMFile_array must start at the index 0 and be contiguous
     * - that is, there can be no element in the indices [0;PEMFile_size-1] which are not a part of the PEM file
     *
     * @param PEMFile_array [IN] The array containing the PEM file
     * @param PEMFile_size  [OUT] The number of elements in the PEM file = last index of the PEM file + 1
     *
     */
    void get_PEM_length(unsigned char * PEMFile_array, size_t * PEMFile_size);

    void get_IDXs(unsigned char* PEMFile, size_t PEMFile_len, int IDXTuple[2]);

    /**
     * @param
     *       PEMFile [IN] the PEM file we would like to get the source of
     *       PEMFile_len [IN] the number of elements in the PEM file
     *       sourceAarray [OUT] Where we store the source of the PEM file
     *       sourceLen [OUT] The size of the source
     */
    void get_source(unsigned char *PEMFile, size_t PEMFile_len, unsigned char **sourceArray, size_t *sourceLen);

    /**
     *
     * @param source [IN] The source we wish to add the PEM headers to
     * @param source_size [IN] The number of elements in the source array
     * @param PEMFile [OUT] The source array plus the beginning and ending PEM header
     * @param PEM_size [OUT] The number of elements in the output
     * @param isPrivate [IN] Do we wish to add private or public PEM headers?
     */

    void add_PEM_headers(unsigned char * source, size_t source_size, unsigned char ** PEMFile, size_t * PEM_size, bool isPrivate);

    void get_pub_beginning_header_size(size_t * pub_beginning_header_size_carrier);

    void get_pub_ending_header_size(size_t * pub_ending_header_size_carrier);
};


#endif //FAGPROJEKTLORA2023_RSAPEMHANDLER_H
