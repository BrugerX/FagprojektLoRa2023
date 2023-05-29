#include "NavigationData.h"

using namespace std;

NavigationData::NavigationData() {
    timestamp = "14:07";
}

char * NavigationData::getTimestamp() {
    return (char *) timestamp.data();
}