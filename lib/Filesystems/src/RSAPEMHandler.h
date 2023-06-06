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
    const char * beginning_header_pattern = "-----BEGIN (PUBLIC|PRIVATE) KEY-----";
    const char * ending_header_pattern = "-----END (PUBLIC|PRIVATE) KEY-----";

private:
    /*
     * Gets the beginning index of the source of the PEM file
     * That is, the PEM file minus the beginning header
     */
    void getBeginIDX(unsigned char *PEMFile, size_t PEMFile_len, int * idx);

    /**
     * Gets the end index of the source of the PEM file
     * That is, the PEM file minus the ending header
     *
     * @param
     *       PEMFile [IN] The PEMFile for which we would like to get the end index of the source
     *       idx [OUT] The int which holds the index for char immediately before the first "-" in "-----END (PUBLIC|PRIAVTE) KEY-----"
     *
     */

    void getEndIDX(unsigned char * PEMFile,size_t PEMFile_len, int * idx);

    void getSourceLen(size_t PEMFile_original_len, int beginIDX, int endIDX, size_t * new_len);
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
};


#endif //FAGPROJEKTLORA2023_RSAPEMHANDLER_H
