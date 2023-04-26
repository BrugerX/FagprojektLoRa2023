#include "DataView.h"
#include "Settings.h"
#include "Member.h"
#include <vector>

using namespace std;

#ifndef DATAMODEL_H
#define DATAMODEL_H

//maybe make a class for groupmembers containing ID, name, location and so on
//then probably rename this to group
class DataModel{
private:
    DataView view;
    char state;
    //char numberOfGroupMembers;
    char tableIndex;
    //char coordinates[32][2];
    vector<Member> groupMembers;



public:
    DataModel(char state, DataView dataView);
    //char tableID[32][8];
    //char tableName[32][8];
    void changeCurrentLocation(char x, char y);
    char findMemberIndex(char * ID);
    void changeMemberLocation(char x, char y, char memberIndex);
    char getTableIndex();
    char getCurrentMemberIndex();
    void changeTableIndex(char userInput);
    char getState();
    void setState(char newState);
    char getNumberOfMembers();
    char * getMemberName(char index);
    char * getMemberTimestamp(char index);

};
#endif //DATAMODEL_H