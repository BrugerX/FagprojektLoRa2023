//
// Created by DripTooHard on 29-05-2023.
//

#include "TestUtility.h"

bool assertNotEqualArrayString(unsigned char * arr1, unsigned char * arr2){
    for(int i = 0; arr1[i] || arr2[i] ;i++){

        //Not the same element, or one string has more elements than the other
        if( arr1[i] != arr2[i] || !arr1[i] || !arr2[i] ){
            return true;
        }
    }

    return false;
}

bool assertNotEqualArray(unsigned char * arr1, unsigned char * arr2, size_t nrElements){
for(int i = 0; i<nrElements;i++){
    if( arr1[i] != arr2[i] ){
        return true;
    }
}

return false;
}