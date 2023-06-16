#include "DataView.h"
#include "DataModel.h"
#include "MVCSettings.h"
#include <ssd1306.h>

using namespace std;

#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H


class DataController{
private:
    DataModel model;
    DataView * view;

public:
    explicit DataController(DataView * dataView); //DataModel datamodel, DataView dataViewet
    void handleUserInput(char userInput);
    char getModelState();
    void addGroupMember(Member groupMember);
    void removeGroupMember(char index);
    void removeGroupMember(Member groupMember);
    char getTableIndex();
    //for testing purposes
    DataModel getModel();
    void setTopTableIndex(char newIndex);
    void setTableIndex(char newIndex);
    void setState(char newState);
};
#endif // DATACONTROLLER_H