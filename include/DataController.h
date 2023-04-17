#include "DataView.h"
#include "DataModel.h"
#include "Settings.h"

using namespace std;

#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H


class DataController{
private:
    char state;
    DataModel model;
    DataView view;
    void updateModel(char input); //many more methods

public:
    DataController(DataModel datamodel, DataView dataView, char state);
    void handleUserInput(char userInput);

};
#endif //DATACONTROLLER_H