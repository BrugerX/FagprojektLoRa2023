//
// Created by DripTooHard on 03-04-2023.
//

#include "Utility.h"


//Prints an unsigned char array into either numerical or text format based on the base
void println_unsignedString(unsigned char * unsginedString,int strlen, int base){

    for(int x = 0; x<strlen;x++){
        unsigned char chr = unsginedString[x];

        if(chr<10 && base == HEX){ //We print the leading 0's in a hexadecimal number
            Serial.print(0);
        }
        Serial.print(chr,base);
    }
    Serial.print("\n");
}


void println_unsignedString(const unsigned char * unsginedString,int strlen, int base){

    for(int x = 0; x<strlen;x++){
        const unsigned char chr = unsginedString[x];

        if(chr<10 && base == HEX){ //We print the leading 0's in a hexadecimal number
            Serial.print(0);
        }
        Serial.print(chr,base);
    }
    Serial.print("\n");
}