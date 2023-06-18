#include "ssd1306.h"
#include <math.h>
#include "freertos/task.h"
#include <string.h>
#include "esp_log.h"
#include "DataView.h"
#include <font8x8_basic.h>
using namespace std;

#define TAG "DataView"

DataView::DataView(){
}

void DataView::showStartScreen() {
    char startText[] = "StartScreen";
    char userInfo1[] = "For compass";
    char userInfo2[] = "press w";
    char userInfo3[] = "For table";
    char userInfo4[] = "press s";
    ssd1306_clear_screen(&dev, 0);
    ssd1306_display_text(&dev, 0, startText, strlen(startText), 0);
    ssd1306_display_text(&dev, 2, userInfo1, strlen(userInfo1), 0);
    ssd1306_display_text(&dev, 3, userInfo2, strlen(userInfo2), 0);
    ssd1306_display_text(&dev, 5, userInfo3, strlen(userInfo3), 0);
    ssd1306_display_text(&dev, 6, userInfo4, strlen(userInfo4), 0);
}

void DataView::drawCircle(int xCenter, int yCenter, int r) {
    for (int i = 0; i < 360; i += 1) {
        double xCord = xCenter + r * cos(i * M_PI/180);
        double yCord = yCenter + r * sin(i * M_PI/180);
        _ssd1306_pixel(&dev, round(xCord),  round(yCord), 0);
        vTaskDelay(1/1000); //delay is necessary for hardware to work
    }
    ESP_LOGD(TAG, "successfully added circle shape to buffer");
    ssd1306_show_buffer(&dev);
    ESP_LOGD(TAG, "successfully show circle display");
}

void DataView::highlightCircle(int xCenter, int yCenter, int r){
    for (int i = 0; i < r; i++) {
        drawCircle(xCenter, yCenter, i);
    }
    ESP_LOGD(TAG, "successfully added highlighted circle shape to buffer");
    ssd1306_show_buffer(&dev);
    ESP_LOGD(TAG, "successfully show highlighted circle on display");
}

void DataView::drawTable(char columns, char rows) {
    char xColumn = (char) 128/columns;
    char yRow = (char) 64/rows;
    for(char i = 1; i < columns; i++) {
        char x = i*xColumn;
        _ssd1306_line(&dev, x, 0, x, 63, 0);
    }
    ESP_LOGD(TAG, "successfully added column lines to buffer");
    for(char i = 1; i <= rows; i++) {
        char y = i*yRow-3;
        _ssd1306_line(&dev, 0, y, 127, y, 0);
    }
    ESP_LOGD(TAG, "successfully added row lines to buffer");
    ssd1306_show_buffer(&dev);
    ESP_LOGD(TAG, "successfully Drew table on display");
}

void DataView::drawCompass() {
    drawTextAt(61, 0, (char *) "N", 1, 0);
    drawTextAt(61, 56, (char *) "S", 1, 0);
    drawTextAt(25, 28, (char *) "W", 1, 0);
    drawTextAt(97, 28, (char *) "E", 1, 0);
    drawCircle(64, 32, 31);
    drawCircle(64, 32, 15);
    ESP_LOGD(TAG, "successfully drew compass on display");
}

//scrolls the current text up (what the user would call scroll down on screen) and inserts new text below.
void DataView::scrollTextUp(char * text, char length) {
    for(char i = 0; i < 8; i++){
        ssd1306_wrap_arround(&dev, SCROLL_UP, 0, 127, 0); //scrolls once start at seg 0 and to seg 127 (the whole line)
    }
    ESP_LOGD(TAG, "successfully scrolled content up by 8 pixels / one page");
    char clearingString[] = "                ";
    //first clearing the current string with the clearingString
    ssd1306_display_text(&dev, 7, clearingString, 16, 0);
    //then printing the new string
    ssd1306_display_text(&dev, 7, text, length, 0);
    ESP_LOGD(TAG, "successfully scrolled text up");
}

void DataView::scrollTextDown(char * text, char length) {
    for(char i = 0; i < 8; i++){
        ssd1306_wrap_arround(&dev, SCROLL_DOWN, 0, 127, 0); //scrolls once start at seg 0 and to seg 127 (the whole line)
    }
    ESP_LOGD(TAG, "successfully scrolled content down by 8 pixels / one page");
    char clearingString[] = "                ";
    //first clearing the current string with the clearingString
    ssd1306_display_text(&dev, 7, clearingString, 16, 0);
    //then printing the new string
    ssd1306_display_text(&dev, 7, text, length, 0);
    ESP_LOGD(TAG, "successfully scrolled text down");
}

void DataView::displayText(char *text) {
    int length = strlen(text);
    if(length <= 128 ){
        if(length <= 16){
            ssd1306_display_text(&dev, 0, text, length, 0);
        }
        else {
            int neededPages = ceil((double) length/ (double) 16);
            for(int page = 0; page < neededPages; page++){
                char subIndexStart = 16 * page;
                char subIndexMax = 16 * page + 15; //end index for substring starting at
                // 16*page and being 16 long (which means it can fit on the display)
                if(length > subIndexMax) { //Strings of length 16 can fit on the screen
                    char newString[16];
                    for (signed char i = 0; i < 16; i++){ //making the substring
                        newString[i] = text[subIndexStart+i];
                    }
                    ssd1306_display_text(&dev, page, newString, 16, 0);
                }
                else { //rest of string is not 16 long, so just copying what's left
                    char newLength = length-subIndexStart;
                    char newString[newLength];
                    for (signed char i = 0; i < newLength; i++){ //making the substring
                        newString[i] = text[subIndexStart+i];
                    }
                    ssd1306_display_text(&dev, page, newString, newLength, 0);
                }
            }
            ESP_LOGD(TAG, "successfully showing all long text on screen");
        }
    }
    else { //all the text don't fit on the display
        for(int page = 0; page < 8; page++) { //first fill the display with text.
            char subString[16];
            int subIndexStart = 16 * page;
            for (signed char i = 0; i < 16; i++) {
                subString[i] = text[subIndexStart+i];
            }
            ssd1306_display_text(&dev, page, subString, 16, 0);
        }
        ESP_LOGD(TAG, "successfully showing first part of long text, that fits on the display");
        vTaskDelay(1000);
        int subIndexStart = 128;
        char neededPages = ceil((double) (length-subIndexStart)/ (double) 16);
        for(char i = 0; i < neededPages-1; i++) {
            char newBottomString[16];
            for (signed char j = 0; j < 16; j++) {
                newBottomString[j] = text[subIndexStart+j];
            }
            subIndexStart += 16;
            scrollTextUp(newBottomString, 16);
            vTaskDelay(10);
        }
        ESP_LOGD(TAG, "successfully scrolled text up and showing next full line of long text");
        signed char restLength = length-subIndexStart;
        char restString[restLength];
        for(signed char i = 0; i < restLength; i++) {
            restString[i] = text[subIndexStart+i];
        }
        scrollTextUp(restString, restLength);
        ESP_LOGD(TAG, "successfully scrolled text up and showing last line of long text");
    }
}

//Draws text starting at the specified location, does not make sure all text fits on screen.
//this method expects 0 <= x <= 127 and 0 <= y <= 63 but will not fail it not satisfied.
//If text is too long, then it overflows 1 pixel down, from the other side.
void DataView::drawTextAt(char x, char y, char *text, char length, bool invert) {
    int textLength = length;
    char offset = 0;
    for(int i = 0; i < textLength; i++){
        uint8_t * image = font8x8_basic_tr[(uint8_t) text[i]];
        for(signed char j = 0; j < 8; j++){
            uint8_t firstbyte  = image[j];
            for(signed char k = 0; k < 8; k++){
                char bit = firstbyte >> k & 1; //taking one bit at a time from the byte
                if(invert) bit = !bit;
                //if bit = 1, meaning it should be there (if no invert), then we add it.
                _ssd1306_pixel(&dev, j+x+offset, k+y, !bit);
                vTaskDelay(1/1000); //delay necessary for hardware to work
            }
        }
        offset += 8;
    }
    ssd1306_show_buffer(&dev);
    ESP_LOGD(TAG, "successfully displayed text at %d, %d", x, y);
}

void DataView::scrollTableUp(char * ID, char * timestamp){ //only display 8 first characters of string
    char clearingString[] = "        ";
    char IDLength = strlen(ID) > 8 ? 8 : strlen(ID);
    char tsLength = strlen(timestamp) > 8 ? 8 : strlen(timestamp);
    for(char j = 0; j < 16; j++){
        ssd1306_wrap_arround(&dev, SCROLL_UP, 0, 127, 0); //scrolls once start at seg 0 and to seg 127 (the whole line)
    }
    ssd1306_display_text(&dev, 6, clearingString, 8, 0);
    drawTextAt(65, 48, clearingString, 8, 0);
    ssd1306_display_text(&dev, 6, ID, IDLength, 0);
    drawTextAt(65, 48, timestamp, tsLength, 0);

}

void DataView::scrollTableDown(char * ID, char * timestamp){ //only display 8 first characters of string
    char clearingString[] = "        ";
    char IDLength = strlen(ID) > 8 ? 8 : strlen(ID);
    char tsLength = strlen(timestamp) > 8 ? 8 : strlen(timestamp);
    for(char j = 0; j < 16; j++){
        ssd1306_wrap_arround(&dev, SCROLL_DOWN, 0, 127, 0); //scrolls once start at seg 0 and to seg 127 (the whole line)
    }
    ssd1306_display_text(&dev, 0, clearingString, 8, 0);
    drawTextAt(65, 0, clearingString, 8, 0);
    ssd1306_display_text(&dev, 0, ID, IDLength, 0);
    drawTextAt(65, 0, timestamp, tsLength, 0);
}

void DataView::drawIDTable(char startIndex, vector<Member> &members){ //only display 8 first characters of string
    drawTable(2, 4);
    //fill the table
    char i;
    unsigned char vlen = members.size();
    unsigned char top = vlen > 4 ? 4 : vlen;
    for(i = 0; i < top; i++){
        char index = (char) std::abs((int)((i+startIndex) % members.size()));
        char * ID = members[index].getID();
        char * timestamp = members[index].getNav().getTimestamp();
        char IDLength = strlen(ID) > 8 ? 8 : strlen(ID);
        char tsLength = strlen(timestamp) > 8 ? 8 : strlen(timestamp);
        ssd1306_display_text(&dev, i*2, ID, IDLength, 0);
        drawTextAt(65, i * 16, timestamp, tsLength, 0);
    }

    ESP_LOGD(TAG, "successfully drew data Table");
}

void DataView::highlightTableCell(char row, char column, char *text, char highlight) {
    char length = strlen(text) > 8 ? 8 : strlen(text);
    if(column){
        drawTextAt(65, row*16, text, length, highlight);
    }
    else {
        ssd1306_display_text(&dev, row*2, text, length, highlight);
    }
}

void DataView::displayNavOverview(char x, char y, bool highlighted) {
    string xText = "x: " + to_string(x);
    string yText = "y: " + to_string(y);
    string suffix = highlighted ? "Yes" : "No";
    string hl = "Highlighted: " + suffix;
    ssd1306_display_text(&dev, 0, (char *) xText.data(), xText.length(), 0);
    ssd1306_display_text(&dev, 2, (char *) yText.data(), yText.length(), 0);
    ssd1306_display_text(&dev, 4, (char *) hl.data(), hl.length(), 0);
}

void DataView::updateNavOverview(bool highlighted) {
    char clearingString[] = "                ";
    ssd1306_display_text(&dev, 4, clearingString, 16, 0);
    string suffix = highlighted ? "Yes" : "No";
    string hl = "Highlighted: " + suffix;
    ssd1306_display_text(&dev, 4, (char *) hl.data(), hl.length(), 0);
}

void DataView::drawMembersOnCompass(vector<Member> &members) {
    for(Member m : members){
        if(m.getHighlight()){
            highlightCircle(m.getXLocation(),m.getYLocation(),MEMBER_CIRCLE_SIZE);
        }
        else{
            drawCircle(m.getXLocation(),m.getYLocation(),MEMBER_CIRCLE_SIZE);
        }
    }
}

void DataView::initialiseView() {
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    //initializing display of size 128x64
    ssd1306_init(&dev, 128, 64);
    ssd1306_contrast(&dev, 0xc3);
    ssd1306_clear_screen(&dev, false);
}

void DataView::clearScreen() {
    ssd1306_clear_screen(&dev, 0);
}