//
// Created by DripTooHard on 06-06-2023.
//

#include "unity.h"
#include <RSAPEMHandler.h>
#include <UnsignedStringUtility.h>

#define HEADER_PUB_BEGIN  "-----BEGIN PUBLIC KEY-----"
#define HEADER_PUB_END  "-----END PUBLIC KEY-----"
#define HEADER_PRIV_BEGIN  "-----BEGIN PRIVATE KEY-----"
#define HEADER_PRIV_END  "-----END PUBLIC KEY-----"

//Randomly chosen actual PEM public key - we need a big key in case a new algorithm only works on inputs of fixed sizes
#define SRC "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMI\0BCgKCAQEAypKRF2xwqQN4PjZOnJ8W5Fa3WQ8f8cK61KDFG3ecNZLYqP0y+Xg+L/xY68CtV0rSWkYqvn/Io1ziDnYkHrznBr54tZ4L59/3jle2I4vln3I6d1X4Ir/nsFdMR5CK3kmSAnijZU2RCtof+szCNa88rL9o9dHLM1c8paxl0WttTgvgboc1Hdf1ghTN7Yat/yy+0T8xUiicRx8DuUGtcq+maypODAPI7nJYDLjgwA2670Vp8eET0GIJlqyBRFIh19UJjK5MyPpFbB6KO9HLZEG7fKnaCK+wj9sXX4rvmoo8Ziev9hUs+QEMqoahlS1krz502FhYAeIMz7NIdBONcvHzEQIDAQAB"

//Sizes
#define HEADER_PUB_BEGIN_SIZE sizeof(HEADER_PUB_BEGIN)/sizeof(HEADER_PUB_BEGIN[0])
#define HEADER_PUB_END_SIZE sizeof(HEADER_PUB_END)/sizeof(HEADER_PUB_END[0])
#define HEADER_PRIV_BEGIN_SIZE sizeof(HEADER_PRIV_BEGIN)/sizeof(HEADER_PUB_BEGIN[0])
#define HEADER_PRIV_END_SIZE sizeof(HEADER_PRIV_END)/sizeof(HEADER_PRIV_END[0])
#define SRC_SIZE sizeof(SRC)/sizeof(SRC[0])


#define NORMAL_PUB_KEY_SIZE  HEADER_PUB_BEGIN_SIZE + SRC_SIZE + HEADER_PUB_END_SIZE
#define NORMAL_PRIV_KEY_SIZE HEADER_PRIV_BEGIN_SIZE + SRC_SIZE + HEADER_PRIV_END_SIZE

const unsigned char * NORMAL_PUB_KEY_FILE = (unsigned char*) HEADER_PUB_BEGIN SRC HEADER_PUB_END;
const unsigned char * NORMAL_PRIV_KEY_FILE = (unsigned char*) HEADER_PRIV_BEGIN SRC HEADER_PRIV_END;

RSAPEMHandler * PEMHandler = new RSAPEMHandler();

void setUp(void) {
    // set stuff up here
}


void tearDown(void) {
    // delete stuff down here
}

void getIDXsWorks(){
    int IDXs[2];
    PEMHandler->get_IDXs((unsigned char *) NORMAL_PUB_KEY_FILE, NORMAL_PUB_KEY_SIZE, IDXs);
    TEST_ASSERT_EQUAL(HEADER_PUB_BEGIN_SIZE-1,IDXs[0]); //|BEGIN\0| =n, PEMFile = |Begin\0Src...| => |BEGIN| = n - 1 => idx(S) = |BEGIN| + 1 -1 = n - 1
    TEST_ASSERT_EQUAL(HEADER_PUB_BEGIN_SIZE + SRC_SIZE -3,IDXs[1]); // |BEGIN\0| = n, |SRC\0| = m => |BEGIN| = n -1, |SRC| = m -1 => |BEGIN+SRC| = n + m -2 => index(C) = |BEGIN+SRC| -1 =n + m - 3
}

/**
 * NOTE: Because we define SRC as a string literal, we get the null terminator.
 * This means, SRC = SRC\0 and SRC_SIZE = |SRC| + 1
 * While the actual so
 */
void normalPubKey(){
    size_t source_size;
    unsigned char * source_arr;
    PEMHandler->get_source((unsigned char *) NORMAL_PUB_KEY_FILE, NORMAL_PUB_KEY_SIZE, &source_arr,
                           (size_t *) &source_size);
    TEST_ASSERT_EQUAL(SRC_SIZE - 1,source_size); //-1 for \0

    log_e("%i",SRC_SIZE);
    //If we have as many elements as the SRC - \0 and all elements match in the same indices, we must have SRC - \0.
    for(int i =0; i<source_size;i++)
    {
        TEST_ASSERT_EQUAL(SRC[i],source_arr[i]);
    }
}

//TODO: NEED TO FINISH THE TESTS FOR THIS
/**
 *
 */
void nullCharInSource()
{

}

void nullCharAtEndOfSource()
{

}

void getSource()
{}

void get_PEM_lengt()
{}

void add_PEM_headers_to_source()
{}

void setup()
{
    delay(500);

    //DON'T PUT ANYTHING BEFORE THIS EXCEPT FOR DELAY!!!!
    UNITY_BEGIN(); //Define stuff after this

    //RUN_TEST(getIDXsWorks);
    RUN_TEST(normalPubKey);
    RUN_TEST(getIDXsWorks);

    UNITY_END(); // stop unit testing

}


void loop()
{

}
