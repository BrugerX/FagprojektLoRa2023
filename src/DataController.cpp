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
        if(userInput == ENTER_KEY) this->model.setState(COMPASS_STATE);
        break;
    case COMPASS_STATE:
        ssd1306_clear_screen(dev, 0);
        this->view.drawCompass(dev);
        if(userInput == UP_KEY) {
            //go back in state (will probably no nothing in the future)
            this->model.setState(START_STATE);
        }
        else if(userInput == DOWN_KEY) {
            //go forward in state
            this->model.setState(TABLE_STATE);
        }
        else if(userInput == LEFT_KEY) {
            if(this->model.getCurrentMember() >= 0)
                this->model.changeCurrentMember(LEFT_KEY);
            //change current highlighted user (highlight another position)
        }
        else if(userInput == RIGHT_KEY) {
            if(this->model.getCurrentMember() >= 0)
                this->model.changeCurrentMember(RIGHT_KEY);
            //change current highlighted user (highlight another position)
        }
        else if(userInput == ENTER_KEY) {
            //change screen to show user info
            //PLACEHOLDER
            ssd1306_clear_screen(dev, 0);
            ssd1306_display_text(dev, 4, "PLACEHOLDER", strlen("PLACEHOLDER"), 0);
        }
        break;
    case TABLE_STATE:
        ssd1306_clear_screen(dev, 0);
        this->view.drawIDTable(this->model.tableID, this->model.tableName, dev);
        if(userInput == ENTER_KEY) {
            //Show more user info
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
