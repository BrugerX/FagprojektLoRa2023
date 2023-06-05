//
// Created by DripTooHard on 04-06-2023.
//

#include "PEMHandler.h"

void PEMHandler::getStartIDX(unsigned char *PEMFile, int * idx) {
    const char * startKeyFormula = "-----BEGIN (PUBLIC|PRIVATE) KEY-----";

    int result = RegexUtil::getEndIDX(PEMFile,PEMPubKeyLen,std::regex(startKeyFormula));;

    if(!isGoodPEMResult(result))
    {
        log_e("FAILED TO FIND STARTING IDX OF PEM FILE\nPattern we tried to match the string with: %s\nThe string: %s",startKeyFormula,PEMFile);
        throw std::logic_error("FAILED TO FIND STARTING IDX OF PEM FILE");
    }

    *idx = result;
}

void PEMHandler::getEndIDX(unsigned char *PEMFile, int *idx)  {
    const char * endKeyFormula = "-----END (PUBLIC|PRIVATE) KEY-----";

    int result = RegexUtil::getStartIDX(PEMFile,PEMPubKeyLen,std::regex(endKeyFormula));;

    if(!isGoodPEMResult(result))
    {
        log_e("FAILED TO FIND STARTING IDX OF PEM FILE\nPattern we tried to match the string with: %s\nThe string: %s",endKeyFormula,PEMFile);
        throw std::logic_error("FAILED TO FIND STARTING IDX OF PEM FILE");
    }

    //getStartIDX returns the idx of the first '-'
    *idx = result-1;

}

void getIDXs(unsigned char* PEMFile, int IDXTuple[2]) {

}
