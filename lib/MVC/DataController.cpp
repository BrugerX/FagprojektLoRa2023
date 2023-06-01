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
        view.showStartScreen(dev);
        if (userInput == UP_KEY) {
            this->model.setState(COMPASS_STATE);
            ssd1306_clear_screen(dev, 0);
            this->view.drawCompass(dev);
        }
        else if (userInput == DOWN_KEY){
            this->model.setState(TABLE_STATE);
            ssd1306_clear_screen(dev, 0);
            model.initializeTable(dev);
        }
        break;
    }
    case COMPASS_STATE:
        if(userInput == BACK_KEY) {
            //go back in state (will probably no nothing in the future)
            this->model.setState(START_STATE);
        }
        break;
    case TABLE_STATE:
        /*char tableID[4][8];
        char timestamp[4][8];
        unsigned char lowerBound;
        model.getCurrentMemberIndex() + 4 > model.getNumberOfMembers() ? lowerBound = model.getNumberOfMembers()-4 : model.getCurrentMemberIndex();
        for(lowerBound; lowerBound < lowerBound+4; lowerBound++){
            char * IDString = model.getMemberID(lowerBound);
            char * timestampString = model.getMemberTimestamp(lowerBound);
            for(unsigned char i=0; i < 8; i++){
                tableID[lowerBound % 4][i] = IDString[i];
                timestamp[lowerBound][i] = timestampString[i];
            }
        }
        this->view.drawIDTable(tableID, timestamp, dev); */
        if(userInput == ENTER_KEY) {
            //Show more user info
        }
        else if (userInput == BACK_KEY){
            model.restartIndexes();
            this->model.setState(START_STATE);
        }
        else {
            this->model.changeTableIndex(userInput, dev);
            //go where to where the input decides in the table
        }
        break;
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