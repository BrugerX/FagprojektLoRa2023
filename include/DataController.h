#include "DataView.h"
#include "DataModel.h"
#include "Settings.h"
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
};
#endif //DATACONTROLLER_H