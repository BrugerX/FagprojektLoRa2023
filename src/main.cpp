#include <Arduino.h>
#include "Cryptography/CryptographicSettings.cpp"

/**
 * Finds the starting index of an RSA key formatted in PEM format  in array
 *
 *
 *
 * \arg PEMBUFFER: An unsigned char containing the PEM file in the format
 *                  {X_0,X_1,...,PEM_EMPTY_PLACEHOLDER,PEMFILE_start,....,\0}
 *                  Where PEM_EMPTY_PLACEHOLDER indicates that the value is not a part of the actual PEM file.
 *
 *                  Notice, that there must be at least 1 PEM_EMPTY_PLACEHOLDER in between the PEMFILE_start, and whatever is in the array before the PEM_EMPTY_PLACEHOLDER.
 *                  This allows for use of the array up intil index(PEMFILE_start-2)
 *
 * \return
 *          The starting index of PEMFILE_start inside the array or PEM_ERR_NO_PEM_FILE if there is no PEM file
 */


int findStartingIndexPEMFile(unsigned char * PEMBuffer, size_t sizeOfBuffer){
    for(int i = sizeOfBuffer;i>0;i--){
        unsigned char c = PEMBuffer[i];
        if(c == PEM_EMPTY_PLACEHOLDER){
            return ++i;
        }

        return PEM_ERR_NO_PEM_FILE;
    }

}


/**
 * Finds the size of an RSA key formatted in PEM format
 *
 * \arg PEMBUFFER: An unsigned char containing the PEM file in the format
 *                  {PEM_EMPTY_PLACEHOLDER,...,PEM_EMPTY_PLACEHOLDER,PEMFILE....,\0}
 *                  Where PEM_EMPTY_PLACEHOLDER indicates that the value is not a part of the actual PEM file.
 *
 *                  Notice, that there can be nothing inbetween the start of the PEMFILE and the end of the array.
 *
 * \return
 *          The size of the PEMFILE or PEM_ERR_NO_PEM_FILE if there is no PEM file
 */
/*
int findStartingIndexPEMFile(unsigned char * PEMBuffer,size_t sizeOfBuffer){
    for(int i = 0; i<sizeOfBuffer;i++){
        unsigned char c = PEMBuffer[i];

        //We've reached the end of the array without encountering anything but PEM_EMPTY_PLACEHOLDERS
        if(c == '\0'){
            return PEM_ERR_NO_PEM_FILE;
        }

        if(c != PEM_EMPTY_PLACEHOLDER){
            return i;
        }

    }

    return PEM_ERR_NO_PEM_FILE;
}*/

void setup() {
// write your initialization code here
}

void loop() {
// write your code here

}