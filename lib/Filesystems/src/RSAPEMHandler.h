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
    const char * pub_ending_header = "-----END PUBLIC KEY-----";
    size_t pub_beginning_header_size = 26;
    size_t pub_ending_header_size = 24;

private:
    /**
     * Gets the beginning index of the source of the PEM file
     * That is, the PEM file minus the beginning header starts including that index
     */
    void getBeginIDX(unsigned char *PEMFile, size_t PEMFile_len, int * idx);

    /**
     * Gets the end index of the source of the PEM file
     * That is, the PEM file minus the ending header ends including that index
     *
     * @param
     *       PEMFile [IN] The PEMFile for which we would like to get the end index of the source
     *       idx [OUT] The int which holds the index for char immediately before the first "-" in "-----END (PUBLIC|PRIAVTE) KEY-----"
     *
     */

    void getEndIDX(unsigned char * PEMFile,size_t PEMFile_len, int * idx);

    void getSourceLen(size_t PEMFile_original_len, int beginIDX, int endIDX, size_t * new_len);

    void addPublicBeginHeader(unsigned char * PEMFile);
    void addPublicEndHeader(unsigned char * PEMFile,size_t src_size);

    void addPrivateBeginHeader(unsigned char * PEMFile);
    void addPrivateEndHeader(unsigned char * PEMFile,size_t src_size);

    void addSrc(unsigned char * PEMFile, size_t src_size);

public:

    void getIDXs(unsigned char* PEMFile,size_t PEMFile_len, int IDXTuple[2]);

    /**
     * @param
     *       PEMFile [IN] the PEM file we would like to get the source of
     *       PEMFile_len [IN] the number of elements in the PEM file
     *       sourceAarray [OUT] Where we store the source of the PEM file
     *       sourceLen [OUT] The size of the source
     */
    void getSource(unsigned char *PEMFile,size_t PEMFile_len, unsigned char **sourceArray, size_t *sourceLen);

    void addPEMHeaders(unsigned char * source,size_t source_size,unsigned char ** PEMFile,size_t PEM_size, bool isPrivate);
};


#endif //FAGPROJEKTLORA2023_RSAPEMHANDLER_H
