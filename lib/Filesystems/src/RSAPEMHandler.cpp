//
// Created by DripTooHard on 04-06-2023.
//

#include "RSAPEMHandler.h"


bool isGoodPEMResult(int result){
    return result != BAD_PEM_RESULT;
}

void RSAPEMHandler::getBeginIDX(unsigned char *PEMFile, size_t PEMFile_len, int * idx) {


    int result = RegexUtil::getEndIDX(PEMFile,PEMFile_len,std::regex(this->beginning_header_pattern));;

    if(!isGoodPEMResult(result))
    {
        log_e("FAILED TO FIND STARTING IDX OF PEM FILE\nPattern we tried to match the string with: %s\nThe string: %s",beginning_header_pattern,PEMFile);
        throw std::logic_error("FAILED TO FIND STARTING IDX OF PEM FILE");
    }

    *idx = result;
}

void RSAPEMHandler::getEndIDX(unsigned char *PEMFile,size_t PEMFile_len, int *idx)  {

    int result = RegexUtil::getStartIDX(PEMFile,PEMFile_len,std::regex(this->ending_header_pattern));;

    if(!isGoodPEMResult(result))
    {
        log_e("FAILED TO FIND STARTING IDX OF PEM FILE\nPattern we tried to match the string with: %s\nThe string: %s",ending_header_pattern,PEMFile);
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

void RSAPEMHandler::getSource(unsigned char *PEMFile,size_t PEMFile_len, unsigned char **sourceArrayPTR, size_t *sourceLen) {
    int IDXs[2], beginIDX,endIDX;
    getIDXs(PEMFile,PEMFile_len,IDXs);

    beginIDX = IDXs[0];
    endIDX = IDXs[1];

    getSourceLen(PEMFile_len,beginIDX,endIDX,sourceLen);

    *sourceArrayPTR = (unsigned char *) malloc( *sourceLen * sizeof(unsigned char));

    for(int i = 0; i<*sourceLen;i++){
        (*sourceArrayPTR)[i] = PEMFile[i + beginIDX];
    }

}

