#include "Member.h"
using namespace std;

Member::Member(char * ID, NavigationData nav){
    this->ID = ID;
    this->nav = nav;
    highlighted = false;
}

void Member::ChangeLocation(char x, char y){
    //nav.changeLocation() //this method should be used to change the gps coordinates, but since we haven't implemented getting them, this does nothing.
}

char Member::getXLocation(){
    //nav.getX
    return 10 + (rand() % 109); // This is only for illustrative purposes.
}

char Member::getYLocation(){
    //nav.getY
    return 5 + (rand() % 55); // This is only for illustrative purposes.
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