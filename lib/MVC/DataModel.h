#include "DataView.h"
#include "MVCSettings.h"
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
    char topTableIndex;
    //char coordinates[32][2];
    vector<Member> groupMembers;



public:
    DataModel(char state, DataView dataView);
    void changeCurrentLocation(char x, char y);
    char findMemberIndex(char * ID);
    void changeMemberLocation(char x, char y, char memberIndex);
    char getTableIndex();
    char getCurrentMemberIndex();
    void changeTableIndex(char userInput, SSD1306_t *dev);
    char getState();
    void setState(char newState);
    char getNumberOfMembers();
    char * getMemberID(char index);
    char * getMemberTimestamp(char index);
    void initializeTable(SSD1306_t * dev);
    void addGroupMember(Member groupMember);
    void removeGroupMember(char index);
    void removeGroupMember(Member groupMember);
    void resetTableIndexes();
    void giveOverview(SSD1306_t *dev);
    void updateOverview(SSD1306_t *dev);
    //for testing
    char getTopTableIndex();
    void setTopTableIndex(char newIndex);
    void setTableIndex(char newIndex);
    bool getMemberHighlight();


};
#endif //DATAMODEL_H