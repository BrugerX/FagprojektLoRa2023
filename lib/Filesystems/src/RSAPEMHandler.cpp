//
// Created by DripTooHard on 04-06-2023.
//

#include "RSAPEMHandler.h"


bool isGoodPEMResult(int result){
    return result != BAD_PEM_RESULT;
}


/**
 * @WARNING USE THIS METHOD TO CREATE PEM ARRAYS AS WE INITIALIZE THE ARRAYS THIS WAY
 *
 * @param PEM_arr [OUT] A pointer to the PEM array
 * @param arr_size [IN] The size you wish the final array to have
 */
void create_PEM_arr(unsigned char ** PEM_arr,size_t arr_size)
{
    unsigned char * temp = (unsigned char *) malloc(sizeof(unsigned char) *arr_size);

    //We initialize it in case a previous PEM file occuppies the same memory space
    fill_char_unsignedString(temp,arr_size,PEM_EMPTY_PLACEHOLDER);
    *PEM_arr = temp;
}

void RSAPEMHandler::get_begin_source_IDX(unsigned char *PEMFile, size_t PEMFile_len, int * idx) {


    int result = RegexUtil::getEndIDX(PEMFile,PEMFile_len,std::regex(this->regex_beginning_header_pattern));;

    if(!isGoodPEMResult(result))
    {
        log_e("FAILED TO FIND STARTING IDX OF PEM FILE SOURCE\nPattern we tried to match the string with: %s\nThe string: %s", regex_beginning_header_pattern, PEMFile);
        throw std::logic_error("FAILED TO FIND STARTING IDX OF PEM FILE SOURCE");
    }

    *idx = result;
}

void RSAPEMHandler::get_end_source_IDX(unsigned char *PEMFile, size_t PEMFile_len, int *idx)  {

    int result = RegexUtil::getStartIDX(PEMFile,PEMFile_len,std::regex(this->regex_ending_header_pattern));;

    if(!isGoodPEMResult(result))
    {
        log_e("FAILED TO FIND STARTING IDX OF PEM FILE\nPattern we tried to match the string with: %s\nThe string: %s", regex_ending_header_pattern, PEMFile);
        throw std::logic_error("FAILED TO FIND STARTING IDX OF PEM FILE");
    }

    //getStartIDX returns the idx of the first '-'
    *idx = result-1;

}

void RSAPEMHandler::get_source_len(size_t PEMFile_original_len, int beginIDX, int endIDX, size_t * new_len){
    *new_len = PEMFile_original_len - beginIDX - (PEMFile_original_len - endIDX - 1);
}

void RSAPEMHandler::get_IDXs(unsigned char* PEMFile, size_t PEMFile_len, int IDXTuple[2]) {
    int start_idx,end_idx;
    get_begin_source_IDX(PEMFile, PEMFile_len, &start_idx);
    get_end_source_IDX(PEMFile, PEMFile_len, &end_idx);

    IDXTuple[0] = start_idx;
    IDXTuple[1] = end_idx;
}

//TODO: Currently it ignores null terminators, we need to fix this, so it just takes the string literal
//Example: BEGIN\0SRC\0END => SRC, not SRC\0
void RSAPEMHandler::get_source(unsigned char *PEMFile, size_t PEMFile_len, unsigned char **sourceArray, size_t *sourceLen) {
    int IDXs[2], beginIDX,endIDX;
    get_IDXs(PEMFile, PEMFile_len, IDXs);

    beginIDX = IDXs[0];
    endIDX = IDXs[1];

    //Gets the size of the source
    get_source_len(PEMFile_len, beginIDX, endIDX, sourceLen);

    *sourceArray = (unsigned char *) malloc(*sourceLen * sizeof(unsigned char));

    //we iterate over the original array and add
    for(int i = 0; i<*sourceLen;i++){
        (*sourceArray)[i] = PEMFile[i + beginIDX];
    }

}



void RSAPEMHandler::add_public_begin_header(unsigned char *PEMFile) {
    for(int i = 0; i<pub_beginning_header_size;i++)
    {
        PEMFile[i] = (unsigned char) pub_beginning_header[i];
    }

}

void RSAPEMHandler::add_public_end_header(unsigned char *PEMFile, size_t src_size) {
    for(int i = 0;i<pub_ending_header_size;i++)
    {
        PEMFile[i + src_size + pub_beginning_header_size] = (unsigned char) pub_ending_header[i];
    }
}


__attribute__((unused)) void RSAPEMHandler::addPrivateBeginHeader(unsigned char *PEMFile)
{}

__attribute__((unused)) void RSAPEMHandler::addPrivateEndHeader(unsigned char *PEMFile, size_t src_size) {}

void RSAPEMHandler::add_src(unsigned char *PEMFile, size_t src_size, unsigned char * source)
{
    for(int i = 0; i<src_size;i++)
    {
        PEMFile[pub_beginning_header_size + i] = source[i];
    }
}

void RSAPEMHandler::add_headers(unsigned char * source, size_t source_size, unsigned char ** PEMFile, size_t * PEM_size, bool isPrivate){
    unsigned char * PEMFile_arr;


    if(isPrivate)
    {

    }

    else
    {
        *PEM_size = source_size + pub_beginning_header_size +pub_ending_header_size;
        PEMFile_arr = (unsigned char *) malloc(sizeof(unsigned char) * (*PEM_size)); //+1 for the null terminator
        add_public_begin_header(PEMFile_arr);
        add_src(PEMFile_arr, source_size, source);
        add_public_end_header(PEMFile_arr, source_size);
    }

    *PEMFile = PEMFile_arr;
}

void RSAPEMHandler::get_pub_beginning_header_size(size_t * pub_beginning_header_size_carrier) {
    *pub_beginning_header_size_carrier = pub_beginning_header_size;
}

void RSAPEMHandler::get_pub_ending_header_size(size_t * pub_ending_header_size_carrier) {
    *pub_ending_header_size_carrier = pub_ending_header_size;
}

void RSAPEMHandler::get_PEM_length(unsigned char *PEMFile_array, size_t *PEMFile_size) {
    size_t IDXs[2],src_start_IDX,src_end_IDX;

    //We assume that all arrays are |PEMFile_array| <= PEMPubKeyLen
    get_IDXs(PEMFile_array,PEMPubKeyLen,(int*)&IDXs);
    src_start_IDX = IDXs[0];
    src_end_IDX = IDXs[1];

    //We check to see if the starting index of the beginning header is 0
    if(src_start_IDX - pub_beginning_header_size + 1 != 0 )
    {
        log_e("STARTING INDEX OF PEM FILE IS %i NOT 0\nTHE PRECONDITION FOR THIS FUNCTION IS THAT THE STARTING INDEX OF THE PEM FILE IS 0 AND THE PEM FILE IS CONTIGUOUS");
        throw std::invalid_argument("PRECONDITION NOT MET - STARTING INDEX OF THE PEM FILE IS NOT 0");
    }

    //Assuming the preconditions hold, we can calculate the PEMFile size easily
    *PEMFile_size = src_end_IDX + pub_ending_header_size;


}
