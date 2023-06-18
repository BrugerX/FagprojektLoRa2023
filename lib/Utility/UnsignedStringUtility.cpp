#include "UnsignedStringUtility.h"

#define CHR 0
#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2


//Prints an unsigned char array into either numerical or text format based on the base
void println_unsignedString(unsigned char * unsginedString,int strlen, int base){

    for(int x = 0; x<strlen;x++){
        unsigned char chr = unsginedString[x];

        if(chr<10 && base == HEX){ //We print the leading 0's in a hexadecimal number
            Serial.print(0);
        }

        Serial.print(chr,base);

        if(base != CHR)
        {
            Serial.print(",");
        }
    }
    Serial.print("\n");
}

//Prints an unsigned char array until the first \0 terminator
void println_unsignedString(unsigned char * unsginedString, int base){

    for(int x = 0; unsginedString[x] ;x++){
        unsigned char chr = unsginedString[x];
        if(chr == '\0') break;

        if(chr<10 && base == HEX){ //We print the leading 0's in a hexadecimal number
            Serial.print(0);
        }
        Serial.print(chr,base);

        if(base != CHR)
        {
            Serial.print(",");
        }
    }
    Serial.print("\n");
}


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
