#include "DataView.h"
#include "DataModel.h"
#include "DataController.h"

#define START_STATE 0
#define COMPASS_STATE 1 
#define TABLE_STATE 2

using namespace std;

DataController::DataController(DataModel datamodel, DataView dataView, char state){
    this->model = datamodel;
    this->view = dataView;
    this->state = state;
}

void DataController::handleUserInput(char userInput){
switch(this->state){
    case START_STATE:
        if(userInput == ENTER_KEY) this->state++;
        break;
    case 1:
    //change to compass
        break;
    default:
    //do nothing
        break;
    }
}
