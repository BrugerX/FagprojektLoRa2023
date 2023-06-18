#include "DataModel.h"
#include <stdexcept>
#include <Arduino.h>

using namespace std;

DataModel::DataModel(char state, DataView * dataView){
    this->state = state;
    this->view = dataView;
    tableIndex = 0;
    topTableIndex = 0;
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
    groupMembers[memberIndex].ChangeLocation(x, y);
}

char DataModel::getTableIndex(){
    return tableIndex;
}

char DataModel::getCurrentMemberIndex(){
    return (char) (tableIndex / 2);
}

void DataModel::changeTableIndex(char userInput) {
    if(groupMembers.size() == 0) return;
    char * currentText = (tableIndex % 2 == 0) ? groupMembers[getCurrentMemberIndex()].getID() : groupMembers[getCurrentMemberIndex()].getNav().getTimestamp();
    view->highlightTableCell(getCurrentMemberIndex()-topTableIndex, tableIndex % 2, currentText, 0);
    if(userInput == UP_KEY){
        getCurrentMemberIndex() == 0 ? : tableIndex-= 2;
    }
    else if(userInput == DOWN_KEY){
        getCurrentMemberIndex() == groupMembers.size()-1 ? : tableIndex+= 2;
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
        view->scrollTableUp(newName, newTimestamp);
    }
    else if (getCurrentMemberIndex() < topTableIndex){
        topTableIndex--;
        char * newName = groupMembers[getCurrentMemberIndex()].getID();
        char * newTimestamp = groupMembers[getCurrentMemberIndex()].getNav().getTimestamp();
        view->scrollTableDown(newName, newTimestamp);
    }
    char * newHighlightedText =(tableIndex % 2 == 0) ? groupMembers[getCurrentMemberIndex()].getID() : groupMembers[getCurrentMemberIndex()].getNav().getTimestamp();
    view->highlightTableCell(getCurrentMemberIndex()-topTableIndex, tableIndex % 2, newHighlightedText, 1);
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

void DataModel::initializeTable(){
    Serial.print("Drawing table with topTableIndex =");
    Serial.println(topTableIndex,DEC);
    view->drawIDTable(topTableIndex, groupMembers);
    if(groupMembers.size() > 0){
        char * text = tableIndex % 2 ? groupMembers[getCurrentMemberIndex()].getNav().getTimestamp() : groupMembers[getCurrentMemberIndex()].getID();
        view->highlightTableCell(tableIndex/2-topTableIndex, tableIndex % 2, text, 1);
    }
}

void DataModel::addGroupMember(Member groupMember){
    if(groupMembers.size() < MAX_NUMBER_OF_MEMBERS){ //we can have a max of 127 members because signed char max is 127
        groupMembers.insert(groupMembers.end(), groupMember);
    }
    else throw length_error("You have to many members, remove some first if you want to add more");
}

//this method uses signed char because the test framework we use interpret the type "char" by default as unsigned char thus
//making it impossible to test negative indexes, unless we specify it here as taking signed char
//This  however makes no difference otherwise as the c++ compiler has char as signed char by default.
void DataModel::removeGroupMember(signed char index) {
    if(index < 0) {
        throw out_of_range("The index has to be non-negative");
    }
    else if(groupMembers.empty()){
        throw length_error("There are no members, you can not delete any");
    }
    else{
        groupMembers.erase(groupMembers.begin() + index);
    }

}

void DataModel::removeGroupMember(Member groupMember) {
    for(unsigned char i = 0; i < groupMembers.size(); i++){
        if(groupMembers[i] == groupMember){
            groupMembers.erase(groupMembers.begin()+i);
        }
    }
}

void DataModel::giveOverview() {
    Member currentMem = groupMembers[getCurrentMemberIndex()];
    view->displayNavOverview(currentMem.getXLocation(), currentMem.getYLocation(), currentMem.getHighlight());
}

void DataModel::updateOverview() {
    groupMembers[getCurrentMemberIndex()].changeHighlight();
    view->updateNavOverview(groupMembers[getCurrentMemberIndex()].getHighlight());
}

void DataModel::drawMembersOnCompass() {
    view->drawMembersOnCompass(groupMembers);
}

void DataModel::resetTableIndexes(){
    topTableIndex = 0;
    tableIndex = 0;
}

//for testing
char DataModel::getTopTableIndex() {
    return topTableIndex;
}

void DataModel::setTableIndex(char newIndex) {
    this->tableIndex = newIndex;
}

void DataModel::setTopTableIndex(char newIndex) {
    this->topTableIndex = newIndex;
}

bool DataModel::getMemberHighlight() {
    return groupMembers[getCurrentMemberIndex()].getHighlight();
}