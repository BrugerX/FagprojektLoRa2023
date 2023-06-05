//
// Created by DripTooHard on 04-06-2023.
//

#ifndef FAGPROJEKTLORA2023_PEMHANDLER_H
#define FAGPROJEKTLORA2023_PEMHANDLER_H

#include <RegexUtility.h>
#include <CryptographicSettings.h>

#define BAD_PEM_RESULT -1

bool isGoodPEMResult(int result){
    return result != BAD_PEM_RESULT;
}

class PEMHandler{
private:
    /*
     * Gets the starting index of the source of the PEM file
     * That is, the PEM file minus the starting header
     */
    void getStartIDX(unsigned char * PEMFile, int * idx);

    /**
     * Gets the end index of the source of the PEM file
     * That is, the PEM file minus the ending header
     *
     * @param
     *       PEMFile [IN] The PEMFile for which we would like to get the end index of the source
     *       idx [OUT] The int which holds the index for char immediately before the first "-" in "-----END (PUBLIC|PRIAVTE) KEY-----"
     *
     */

    void getEndIDX(unsigned char * PEMFile, int * idx);
public:

    void getIDXs(unsigned char* PEMFile, int IDXTuple[2]);
};


#endif //FAGPROJEKTLORA2023_PEMHANDLER_H
