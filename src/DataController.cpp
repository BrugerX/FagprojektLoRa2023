#include "DataView.h"
#include "DataModel.h"
#include "DataController.h"
#include <ssd1306.h>
#include "string.h"

using namespace std;

DataController::DataController(DataView dataView) : model(0, dataView) {
    //this->model = model;
    this->view = dataView;
}

void DataController::handleUserInput(char userInput, SSD1306_t * dev){
switch(this->model.getState()){
    case START_STATE:
        ssd1306_clear_screen(dev, 0);
        ssd1306_display_text(dev, 4, "StartScreen", strlen("StartScreen"), 0);
        if(userInput == UP_KEY) this->model.setState(COMPASS_STATE);
        else if(userInput == DOWN_KEY) this->model.setState(TABLE_STATE);
        break;
    case COMPASS_STATE:
        ssd1306_clear_screen(dev, 0);
        this->view.drawCompass(dev);
        if(userInput == BACK_KEY) {
            //go back in state (will probably no nothing in the future)
            this->model.setState(this->model.getState()-1);
        }
        break;
    case TABLE_STATE:
        ssd1306_clear_screen(dev, 0);
        char tableID[4][8];
        char timestamp[4][8];
        unsigned char lowerBound;
        model.getCurrentMemberIndex() + 4 > model.getNumberOfMembers() ? lowerBound = model.getNumberOfMembers()-4 : model.getCurrentMemberIndex();
        for(lowerBound; lowerBound < lowerBound+4; lowerBound++){
            char * IDString = model.getMemberName(lowerBound);
            char * timestampString = model.getMemberTimestamp(lowerBound);
            for(unsigned char i=0; i < 8; i++){
                tableID[lowerBound][i] = IDString[i];
                timestamp[lowerBound][i] = timestampString[i];
            }
        }
        this->view.drawIDTable(tableID, timestamp, dev);
        if(userInput == ENTER_KEY) {
            //Show more user info
        }
        else if (userInput == BACK_KEY){
            this->model.setState(this->model.getState()-1);
        }
        else {
            this->model.changeTableIndex(userInput);
            //go where to where the input decides in the table
        }
        break;
    default:
    //do nothing
        break;
    }
}
