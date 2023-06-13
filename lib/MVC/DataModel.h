#include "DataView.h"
#include "MVCSettings.h"
#include "Member.h"
#include <vector>

using namespace std;

#ifndef DATAMODEL_H
#define DATAMODEL_H

//A model containing all members in the group, as well as information about states and position in the table
class DataModel{
private:
    DataView * view;
    char state;
    char tableIndex;
    char topTableIndex;
    vector<Member> groupMembers;



public:
    DataModel(char state, DataView * dataView);
    void changeCurrentLocation(char x, char y);
    char findMemberIndex(char * ID);
    void changeMemberLocation(char x, char y, char memberIndex);
    char getTableIndex();
    char getCurrentMemberIndex();
    void changeTableIndex(char userInput);
    char getState();
    void setState(char newState);
    char getNumberOfMembers();
    char * getMemberID(char index);
    char * getMemberTimestamp(char index);
    void initializeTable();
    void addGroupMember(Member groupMember);
    void removeGroupMember(signed char index);
    void removeGroupMember(Member groupMember);
    void resetTableIndexes();
    void giveOverview();
    void updateOverview();
    void drawMembersOnCompass();
    //for testing
    char getTopTableIndex();
    void setTopTableIndex(char newIndex);
    void setTableIndex(char newIndex);
    bool getMemberHighlight();
};
#endif // DATAMODEL_H