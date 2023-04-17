#include "DataView.h"
#include "Settings.h"

using namespace std;

#ifndef DATAMODEL_H
#define DATAMODEL_H

//maybe make a class for groupmembers containing ID, name, location and so on
//then probably rename this to group
class DataModel{
private:
    char tableID[32][8];
    char tableName[32][8];
    char numberOfGroupMembers;
    char tableIndex;
    char coordinates[32][2];
    char currentMember;


public:
    DataModel();
    void changeCurrentLocation(char userInput);
    char findMember(char * ID);
    void changeMemberLocation(char userInput, char memberIndex);
    char getTableIndex();
    char getCurrentMember();

};
#endif //DATAMODEL_H