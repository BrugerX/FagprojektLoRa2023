//
// Created by DripTooHard on 04-06-2023.
//

#include "RSAPEMHandler.h"


bool isGoodPEMResult(int result){
    return result != BAD_PEM_RESULT;
}

void RSAPEMHandler::getBeginIDX(unsigned char *PEMFile, size_t PEMFile_len, int * idx) {


    int result = RegexUtil::getEndIDX(PEMFile,PEMFile_len,std::regex(this->regex_beginning_header_pattern));;

    if(!isGoodPEMResult(result))
    {
        log_e("FAILED TO FIND STARTING IDX OF PEM FILE\nPattern we tried to match the string with: %s\nThe string: %s", regex_beginning_header_pattern, PEMFile);
        throw std::logic_error("FAILED TO FIND STARTING IDX OF PEM FILE");
    }

    *idx = result;
}

void RSAPEMHandler::getEndIDX(unsigned char *PEMFile,size_t PEMFile_len, int *idx)  {

    int result = RegexUtil::getStartIDX(PEMFile,PEMFile_len,std::regex(this->regex_ending_header_pattern));;

    if(!isGoodPEMResult(result))
    {
        log_e("FAILED TO FIND STARTING IDX OF PEM FILE\nPattern we tried to match the string with: %s\nThe string: %s", regex_ending_header_pattern, PEMFile);
        throw std::logic_error("FAILED TO FIND STARTING IDX OF PEM FILE");
    }

    //getStartIDX returns the idx of the first '-'
    *idx = result-1;

}

void RSAPEMHandler::getSourceLen(size_t PEMFile_original_len, int beginIDX, int endIDX, size_t * new_len){
    *new_len = PEMFile_original_len - beginIDX - (PEMFile_original_len - endIDX - 1);
}

void RSAPEMHandler::getIDXs(unsigned char* PEMFile,size_t PEMFile_len, int IDXTuple[2]) {
    int start_idx,end_idx;
    getBeginIDX(PEMFile,PEMFile_len, &start_idx);
    getEndIDX(PEMFile,PEMFile_len,&end_idx);

    IDXTuple[0] = start_idx;
    IDXTuple[1] = end_idx;
}

//TODO: Currently it ignores null terminators, we need to fix this, so it just takes the string literal
//Example: BEGIN\0SRC\0END => SRC, not SRC\0
void RSAPEMHandler::getSource(unsigned char *PEMFile,size_t PEMFile_len, unsigned char **sourceArrayPTR, size_t *sourceLen) {
    int IDXs[2], beginIDX,endIDX;
    getIDXs(PEMFile,PEMFile_len,IDXs);

    beginIDX = IDXs[0];
    endIDX = IDXs[1];

    //Gets the size of the source
    getSourceLen(PEMFile_len,beginIDX,endIDX,sourceLen);

    *sourceArrayPTR = (unsigned char *) malloc( *sourceLen * sizeof(unsigned char));

    //we iterate over the original array and add
    for(int i = 0; i<*sourceLen;i++){
        (*sourceArrayPTR)[i] = PEMFile[i + beginIDX];
    }

}



void RSAPEMHandler::addPublicBeginHeader(unsigned char *PEMFile) {
    for(int i = 0; i<pub_beginning_header_size;i++)
    {
        PEMFile[i] = (unsigned char) pub_beginning_header[i];
    }

}

void RSAPEMHandler::addPublicEndHeader(unsigned char *PEMFile, size_t src_size) {
    for(int i = 0;i<pub_ending_header_size;i++)
    {
        PEMFile[i + src_size + pub_beginning_header_size] = (unsigned char) pub_ending_header[i];
    }
}


void RSAPEMHandler::addPrivateBeginHeader(unsigned char *PEMFile)
{}

void RSAPEMHandler::addPrivateEndHeader(unsigned char *PEMFile, size_t src_size) {}

void RSAPEMHandler::addSrc(unsigned char *PEMFile, size_t src_size, unsigned char * source)
{
    for(int i = 0; i<src_size;i++)
    {
        PEMFile[pub_beginning_header_size + i] = source[i];
    }
}

void RSAPEMHandler::addPEMHeaders(unsigned char * source,size_t source_size,unsigned char ** PEMFile,size_t * PEM_size, bool isPrivate){
    unsigned char * PEMFile_arr;


    if(isPrivate)
    {

    }

    else
    {
        *PEM_size = source_size + pub_beginning_header_size +pub_ending_header_size + 1;
        PEMFile_arr = (unsigned char *) malloc(sizeof(unsigned char) * (*PEM_size)); //+1 for the null terminator
        addPublicBeginHeader(PEMFile_arr);
        addSrc(PEMFile_arr,source_size,source);
        addPublicEndHeader(PEMFile_arr,source_size);
    }

    PEMFile_arr[*PEM_size] = (unsigned char) '\0';

    *PEMFile = PEMFile_arr;
}
