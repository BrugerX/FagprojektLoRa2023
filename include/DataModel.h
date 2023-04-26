#include "DataView.h"
#include "Settings.h"

using namespace std;

#ifndef DATAMODEL_H
#define DATAMODEL_H

//maybe make a class for groupmembers containing ID, name, location and so on
//then probably rename this to group
class DataModel{
private:
    DataView view;
    char state;
    char numberOfGroupMembers;
    char tableIndex;
    char coordinates[32][2];
    char currentMember;


public:
    DataModel(char state, DataView dataView);
    char tableID[32][8];
    char tableName[32][8];
    void changeCurrentLocation(char userInput);
    char findMember(char * ID);
    void changeMemberLocation(char userInput, char memberIndex);
    char getTableIndex();
    char getCurrentMember();
    void changeCurrentMember(char userInput);
    void changeTableIndex(char userInput);
    char getState();
    void setState(char newState);

};
#endif //DATAMODEL_H