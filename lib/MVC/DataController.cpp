#include "DataView.h"
#include "DataModel.h"
#include "DataController.h"
#include <ssd1306.h>
#include <string.h>


using namespace std;

DataController::DataController(DataView * dataView) : model(0, dataView) {
    //this->model = model;
    this->view = dataView;
}

void DataController::handleUserInput(char userInput){
switch(this->model.getState()){
    case START_STATE: {
        if (userInput == UP_KEY) {
            view->clearScreen();
            this->view->drawCompass();
            model.drawMembersOnCompass();
            this->model.setState(COMPASS_STATE);
        }
        else if (userInput == DOWN_KEY){
            view->clearScreen();
            model.initializeTable();
            this->model.setState(TABLE_STATE);
        }
        break;
    }
    case COMPASS_STATE:
        if(userInput == BACK_KEY) {
            //go back in state
            view->clearScreen();
            view->showStartScreen();
            this->model.setState(START_STATE);
        }
        break;
    case TABLE_STATE:
        if(userInput == ENTER_KEY) {
            view->clearScreen();
            model.giveOverview();
            model.setState(NAV_OVERVIEW_STATE);
        }
        else if (userInput == BACK_KEY){
            model.resetTableIndexes();
            view->clearScreen();
            view->showStartScreen();
            this->model.setState(START_STATE);
        }
        else {
            this->model.changeTableIndex(userInput);
            //go where to where the input decides in the table
        }
        break;
    case NAV_OVERVIEW_STATE:
        if(userInput == ENTER_KEY){
            model.updateOverview();
        }
        else if(userInput == BACK_KEY){
            view->clearScreen();
            //model.resetTableIndexes();
            model.initializeTable();
            model.setState(TABLE_STATE);
        }
    default:
    //do nothing
        break;
    }
}

char DataController::getModelState(){
    return model.getState();
}

void DataController::addGroupMember(Member groupMember){
    model.addGroupMember(groupMember);
}

char DataController::getTableIndex(){
    return model.getTableIndex();
}

void DataController::removeGroupMember(char index){
    model.removeGroupMember(index);
}

void DataController::removeGroupMember(Member groupMember){
    model.removeGroupMember(groupMember);
}

DataModel DataController::getModel() { //method used for testing
    return model;
}

void DataController::setTableIndex(char newIndex) {
    model.setTableIndex(newIndex);
}

void DataController::setTopTableIndex(char newIndex) {
    model.setTopTableIndex(newIndex);
}

void DataController::setState(char newState) {
    model.setState(newState);
}