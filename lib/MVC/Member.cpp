#include "Member.h"
using namespace std;

Member::Member(char * ID, NavigationData nav){
    this->ID = ID;
    this->nav = nav;
    highlighted = false;
}

void Member::ChangeLocation(char x, char y){
    //nav.changeLocation()
}

char Member::getXLocation(){
    //nav.getX
    return 10 + (rand() % 109);//64;
}

char Member::getYLocation(){
    //nav.getY
    return 5 + (rand() % 55);//32;
}

char * Member::getID(){
    return this->ID;
}

NavigationData Member::getNav() {
    return this->nav;
}

void Member::changeHighlight() {
    highlighted = !highlighted;
}

bool Member::getHighlight() {
    return highlighted;
}