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

//Generates the following array ReGex [A,B,C,...,z]^(|[A,B,C,...,z]|%(sizeOf))
void fill_alphanumeric_unsignedString(unsigned char * unsignedString, size_t sizeOf){
    unsigned char a = 'A';

    for(int i = 0; i<sizeOf;i++){
        unsignedString[i] = a++;

        //91 is not an alphanumeric char
        if(a == 91){
            a = 97; //The ASCII value for 'a'
        } else if(a == 122){
            a = 65; //ASCII for 'A'
        }
    }
}

void fill_char_unsignedString(unsigned char * unsignedString, size_t sizeOf,unsigned char chosenChar){
    for(int i = 0; i<sizeOf;i++){
        unsignedString[i] = chosenChar;
    }
}