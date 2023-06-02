#include "DataModel.h"
#include <stdexcept>

using namespace std;

DataModel::DataModel(char state, DataView dataView){
    this->state = state;
    view = dataView;
    tableIndex = 0;
    topTableIndex = 0;
    //constructor
}

void DataModel::changeCurrentLocation(char x, char y){

}

char DataModel::findMemberIndex(char * ID){
    for (unsigned char i; i < groupMembers.size(); i++){
        if(groupMembers[i].getID() == ID) return i;
    }
    return -1;
}

void DataModel::changeMemberLocation(char x, char y, char memberIndex){
    //potentially coordinates need to be changed
    groupMembers[memberIndex].ChangeLocation(x, y);
}

char DataModel::getTableIndex(){
    return tableIndex;
}

char DataModel::getCurrentMemberIndex(){ //maybe this shouldn't be here
    return (char) (tableIndex / 2);
}

void DataModel::changeTableIndex(char userInput, SSD1306_t *dev) {
    //should probably remove highlight of previously highlighted message
    char * currentText = (tableIndex % 2 == 0) ? groupMembers[getCurrentMemberIndex()].getID() : groupMembers[getCurrentMemberIndex()].getNav().getTimestamp();
    view.highlightTableCell(getCurrentMemberIndex()-topTableIndex, tableIndex % 2, currentText, 0, dev);
    if(userInput == UP_KEY){
        getCurrentMemberIndex() == 0 ? /*tableIndex = (groupMembers.size()*2-2 + tableIndex % 2)*/ : tableIndex-= 2;
    }
    else if(userInput == DOWN_KEY){
        getCurrentMemberIndex() == groupMembers.size()-1 ? /*tableIndex = (0 + tableIndex % 2)*/ : tableIndex+= 2;
    }
    else if(userInput == LEFT_KEY){
        (tableIndex % 2) == 0 ? tableIndex++ : tableIndex--;
    }
    else if(userInput == RIGHT_KEY) {
        (tableIndex % 2) == 1 ? tableIndex-- : tableIndex++;
    }
    //finding out if table should be scrolled
    if (getCurrentMemberIndex() > topTableIndex + 3){
        topTableIndex++;
        char * newName = groupMembers[getCurrentMemberIndex()].getID();
        char * newTimestamp = groupMembers[getCurrentMemberIndex()].getNav().getTimestamp();
        view.scrollTableUp(dev, newName, newTimestamp);
    }
    else if (getCurrentMemberIndex() < topTableIndex){
        topTableIndex--;
        char * newName = groupMembers[getCurrentMemberIndex()].getID();
        char * newTimestamp = groupMembers[getCurrentMemberIndex()].getNav().getTimestamp();
        view.scrollTableDown(dev, newName, newTimestamp);
    }
    char * newHighlightedText =(tableIndex % 2 == 0) ? groupMembers[getCurrentMemberIndex()].getID() : groupMembers[getCurrentMemberIndex()].getNav().getTimestamp();
    view.highlightTableCell(getCurrentMemberIndex()-topTableIndex, tableIndex % 2, newHighlightedText, 1, dev);
}

char DataModel::getState(){
    return state;
}

void DataModel::setState(char newState){
    state = newState;
}

char DataModel::getNumberOfMembers(){
    return (char) groupMembers.size();
}

char * DataModel::getMemberID(char index){
    return groupMembers[index].getID();
}

char * DataModel::getMemberTimestamp(char index){
    return groupMembers[index].getNav().getTimestamp();
}

void DataModel::initializeTable(SSD1306_t * dev){
    view.drawIDTable(topTableIndex, groupMembers, dev);
    view.highlightTableCell(0, 0, groupMembers[0].getID(), 1, dev);
}

void DataModel::addGroupMember(Member groupMember){
    if(groupMembers.size() < MAX_NUMBER_OF_MEMBERS){ //we can have a max of 255 members because unsigned char max is 255
        groupMembers.insert(groupMembers.end(), groupMember);
    }
    else throw length_error("You have to many members, remove some first if you want to add more");
}

void DataModel::removeGroupMember(char index) {//expects a non-negative index, and a that the vector is non-empty
    groupMembers.erase(groupMembers.begin() + index);
}

void DataModel::removeGroupMember(Member groupMember) {
    for(unsigned char i = 0; i < groupMembers.size(); i++){
        if(groupMembers[i] == groupMember){
            groupMembers.erase(groupMembers.begin()+i);
        }
    }
}

void DataModel::resetTableIndexes(){
    topTableIndex = 0;
    tableIndex = 0;
}
