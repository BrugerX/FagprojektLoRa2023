#include "DataView.h"
#include "DataModel.h"
#include "DataController.h"
#include <ssd1306.h>
#include <string.h>


using namespace std;

DataController::DataController(DataView dataView) : model(0, dataView) {
    //this->model = model;
    this->view = dataView;
}

void DataController::handleUserInput(char userInput, SSD1306_t * dev){
switch(this->model.getState()){
    case START_STATE: {
        if (userInput == UP_KEY) {
            ssd1306_clear_screen(dev, 0);
            this->view.drawCompass(dev);
            this->model.setState(COMPASS_STATE);
        }
        else if (userInput == DOWN_KEY){
            ssd1306_clear_screen(dev, 0);
            model.initializeTable(dev);
            this->model.setState(TABLE_STATE);
        }
        break;
    }
    case COMPASS_STATE:
        if(userInput == BACK_KEY) {
            //go back in state
            ssd1306_clear_screen(dev, 0);
            view.showStartScreen(dev);
            this->model.setState(START_STATE);
        }
        break;
    case TABLE_STATE:
        if(userInput == ENTER_KEY) {
            ssd1306_clear_screen(dev, 0);
            model.giveOverview(dev);
            model.setState(NAV_OVERVIEW_STATE);
        }
        else if (userInput == BACK_KEY){
            model.resetTableIndexes();
            ssd1306_clear_screen(dev, 0);
            view.showStartScreen(dev);
            this->model.setState(START_STATE);
        }
        else {
            this->model.changeTableIndex(userInput, dev);
            //go where to where the input decides in the table
        }
        break;
    case NAV_OVERVIEW_STATE:
        if(userInput == ENTER_KEY){
            model.updateOverview(dev);
        }
        else if(userInput == BACK_KEY){
            ssd1306_clear_screen(dev, 0);
            //model.resetTableIndexes();
            model.initializeTable(dev);
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