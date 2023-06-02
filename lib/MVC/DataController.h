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
    DataView view;
    void updateModel(char input); //many more methods

public:
    DataController(DataView dataView); //DataModel datamodel, DataView dataView
    void handleUserInput(char userInput, SSD1306_t * dev);
    char getModelState();
    void addGroupMember(Member groupMember);
    void removeGroupMember(char index);
    void removeGroupMember(Member groupMember);
    char getTableIndex();
    DataModel getModel(); //for testing purposes
};
#endif //DATACONTROLLER_H