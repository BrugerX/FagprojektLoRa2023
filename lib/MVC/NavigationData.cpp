#include "NavigationData.h"

using namespace std;

NavigationData::NavigationData() {
    timestamp = "14:07"; //this is only for illustrative purposes, this should be a timestamp gotten from the data collected, but this is not fully implemented.
}

char * NavigationData::getTimestamp() {
    return (char *) timestamp.data();
}