#include "NavigationData.h"
#include <string.h>
using namespace std;



#ifndef MEMBER_H
#define MEMBER_H
class Member {
    private:
    char * ID;
    NavigationData nav;

    public:
    Member(char * ID, NavigationData nav);
    void ChangeLocation(char x, char y);
    char getXLocation();
    char getYLocation();
    char * getID();
    NavigationData getNav();
    bool operator==(Member &m){
        return strcmp(this->ID, m.ID) == 0 && strcmp(this->nav.getTimestamp(), m.nav.getTimestamp()) == 0;
    }

};


#endif // MEMBER_H