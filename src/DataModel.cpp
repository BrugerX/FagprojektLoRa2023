#include "DataModel.h"


using namespace std;

DataModel::DataModel(char state, DataView dataView){
    this->state = state;
    view = dataView;
    //constructor
}

void DataModel::changeCurrentLocation(char x, char y){

}

char DataModel::findMemberIndex(char * ID){
    for (unsigned char i; i < groupMembers.size(); i++){
        if(groupMembers[i].getID() == ID) return i;
    }
}

void DataModel::changeMemberLocation(char x, char y, char memberIndex){
    //potentially coordinates need to be changed
    groupMembers[memberIndex].ChangeLocation(x, y);
}

char DataModel::getTableIndex(){
    return tableIndex;
}

char DataModel::getCurrentMemberIndex(){ //maybe this shouldn't be here
    return tableIndex / 2;
}

void DataModel::changeTableIndex(char userInput){
    if(userInput == UP_KEY){
        getCurrentMemberIndex() == 0 ? tableIndex = (groupMembers.size()*2-2 + tableIndex % 2) : tableIndex+= 2;
    }
    else if(userInput == DOWN_KEY){
        getCurrentMemberIndex() == groupMembers.size() ? tableIndex = (0 + tableIndex % 2) : tableIndex-= 2;
    }
    else if(userInput == LEFT_KEY){
        (tableIndex % 2) == 0 ? tableIndex++ : tableIndex--;
    }
    else { //user pressed RIGHT_KEY
        (tableIndex % 2) == 1 ? tableIndex-- : tableIndex++;
    }
}

char DataModel::getState(){
    return state;
}

void DataModel::setState(char newState){
    state = newState;
}

char DataModel::getNumberOfMembers(){
    return groupMembers.size();
}

char * DataModel::getMemberName(char index){
    return groupMembers[index].getID();
}

char * DataModel::getMemberTimestamp(char index){
    return groupMembers[index].getNav().getTimestamp();
}
