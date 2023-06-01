#include "NavigationData.h"
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

};


#endif // MEMBER_H