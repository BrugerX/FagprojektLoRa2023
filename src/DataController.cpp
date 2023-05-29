#include "DataView.h"
#include "DataModel.h"
#include "DataController.h"
#include <ssd1306.h>
#include <string.h>
#include <Arduino.h>

using namespace std;

DataController::DataController(DataView dataView) : model(0, dataView) {
    //this->model = model;
    this->view = dataView;
}

void DataController::handleUserInput(char userInput, SSD1306_t * dev){
switch(this->model.getState()){
    case START_STATE: {
        char startText[] = "StartScreen";
        ssd1306_clear_screen(dev, 0);
        ssd1306_display_text(dev, 4, startText, strlen(startText), 0);
        if (userInput == UP_KEY) {
            this->model.setState(COMPASS_STATE);
            ssd1306_clear_screen(dev, 0);
            this->view.drawCompass(dev);
        }
        else if (userInput == DOWN_KEY){
            this->model.setState(TABLE_STATE);
            ssd1306_clear_screen(dev, 0);
            model.initializeTable(dev);
            Serial.print("stateChanging: ");
            Serial.println(getTableIndex(),DEC);
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
        Serial.print("Start of switch: ");
        Serial.println(getTableIndex(),DEC);
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
            this->model.setState(START_STATE);
        }
        else {
            Serial.print("Changing index: ");
            Serial.println(getTableIndex(),DEC);
            this->model.changeTableIndex(userInput, dev);
            Serial.print("Changed index: ");
            Serial.println(getTableIndex(),DEC);
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