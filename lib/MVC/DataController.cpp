#include "DataView.h"
#include "DataModel.h"
#include "DataController.h"
#include <ssd1306.h>
#include <string.h>
#include <Arduino.h>


using namespace std;

DataController::DataController(DataView * dataView) : model(0, dataView) {
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
            //go to where the input decides in the table
        }
        break;
    case NAV_OVERVIEW_STATE:
        if(userInput == ENTER_KEY){
            model.updateOverview();
        }
        else if(userInput == BACK_KEY){
            view->clearScreen();
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
    try {
        model.addGroupMember(groupMember);
    }
    catch (const exception& e){
        Serial.println(e.what()); //for now just printing on serial monitor.
    }
}

char DataController::getTableIndex(){
    return model.getTableIndex();
}

void DataController::removeGroupMember(char index){
    try{
        model.removeGroupMember(index);
    }
    catch (const exception& e){
        Serial.println(e.what()); //for now just printing on serial monitor.
    }
}

void DataController::removeGroupMember(Member groupMember){
    model.removeGroupMember(groupMember);
}

//methods used for testing
DataModel DataController::getModel() {
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