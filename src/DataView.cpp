extern "C" {
#include "ssd1306.h"
#include <math.h>
#include "freertos/task.h"
#include <string.h>
#include "esp_log.h"
}
#include "DataView.h"
#include <font8x8_basic.h>
using namespace std;

#define TAG "DataView"


DataView::DataView(){}

void DataView::drawCircle(int xCenter, int yCenter, int r, SSD1306_t * dev) {
    for (int i = 0; i < 360; i += 1) {
        double xCord = xCenter + r * cos(i * M_PI/180);
        double yCord = yCenter + r * sin(i * M_PI/180);
        _ssd1306_pixel(dev, round(xCord),  round(yCord), 0);
        vTaskDelay(1/1000);
    }
    ESP_LOGD(TAG, "successfully added circle shape to buffer");
    ssd1306_show_buffer(dev);
    ESP_LOGD(TAG, "successfully show circle display");
}

void DataView::highlightCircle(int xCenter, int yCenter, int r, SSD1306_t * dev){
    for (int i = 0; i < r; i++) {
        drawCircle(xCenter, yCenter, i, dev);
    }
    ESP_LOGD(TAG, "successfully added highlighted circle shape to buffer");
    ssd1306_show_buffer(dev);
    ESP_LOGD(TAG, "successfully show highlighted circle on display");
}

void DataView::drawTable(char columns, char rows, SSD1306_t * dev) {
    char xColumn = (char) 128/columns;
    char yRow = (char) 64/rows;
    for(char i = 1; i < columns; i++) {
        char x = i*xColumn;
        _ssd1306_line(dev, x, 0, x, 63, 0);
    }
    ESP_LOGD(TAG, "successfully added column lines to buffer");
    for(char i = 1; i <= rows; i++) {
        char y = i*yRow-3;
        _ssd1306_line(dev, 0, y, 127, y, 0);
    }
    ESP_LOGD(TAG, "successfully added row lines to buffer");
    ssd1306_show_buffer(dev);
    ESP_LOGD(TAG, "successfully Drew table on display");
}

void DataView::drawCompass(SSD1306_t * dev) {
    /*uint8_t N[7] = {0xff,0x06,0x0c,0x18,0x30,0x60,0xff};
    uint8_t S[7] = {0x42,0x85,0x8d,0x99,0xb1,0xa1,0x42};
    uint8_t E_top[7] = {0xf0,0xf0,0xb0,0xb0,0xb0,0xb0,0x30};
    uint8_t E_bottom[7] = {0x0f,0x0f,0x0d,0x0d,0x0d,0x0d,0x0c};
    uint8_t W_top[7] = {0xf0,0xf0,0x00,0x00,0x00,0xf0,0xf0};
    uint8_t W_bottom[7] = {0x0f,0x0f,0x06,0x03,0x06,0x0f,0x0f};*/
    //char width = 7;
    drawTextAt(61, 0, (char*) "N", 0, dev);
    drawTextAt(61, 56, (char*) "S", 0, dev);
    drawTextAt(25, 28, (char*)"W", 0, dev);
    drawTextAt(97, 28, (char*) "E", 0, dev);
    drawCircle(64, 32, 31, dev);
    drawCircle(64, 32, 15, dev);
    //ssd1306_show_buffer(dev);

    /*ssd1306_display_image(dev, 0, (int) 64-width/2, N, width);
    ssd1306_display_image(dev, 7, (int) 64-width/2, S, width);
    ssd1306_display_image(dev, 3, 32-width, W_top, width);
    ssd1306_display_image(dev, 4, 32-width, W_bottom, width);
    ssd1306_display_image(dev, 3, 97, E_top, width);
    ssd1306_display_image(dev, 4, 97, E_bottom, width);*/
    ESP_LOGD(TAG, "successfully drew compass on display");
}

//scrolls the current text up (what the user would call scroll down) and inserts new text below.
void DataView::scrollTextUp(SSD1306_t * dev, char * text, char length) {
    for(char i = 0; i < 8; i++){
        ssd1306_wrap_arround(dev, SCROLL_UP, 0, 127, 0); //scrolls once start at seg 0 and to seg 127 (the whole line)
    }
    ESP_LOGD(TAG, "successfully scrolled content up by 8 pixels / one page");
    char clearingString[] = "                ";
    //first clearing the current string with the clearingString
    ssd1306_display_text(dev, 7, clearingString, 16, 0);
    //then printing the new string
    ssd1306_display_text(dev, 7, text, length, 0);
    ESP_LOGD(TAG, "successfully scrolled text up");
}

void DataView::scrollTextDown(SSD1306_t * dev, char * text, char length) {
    for(char i = 0; i < 8; i++){
        ssd1306_wrap_arround(dev, SCROLL_DOWN, 0, 127, 0); //scrolls once start at seg 0 and to seg 127 (the whole line)
    }
    ESP_LOGD(TAG, "successfully scrolled content down by 8 pixels / one page");
    char clearingString[] = "                ";
    //first clearing the current string with the clearingString
    ssd1306_display_text(dev, 7, clearingString, 16, 0);
    //then printing the new string
    ssd1306_display_text(dev, 7, text, length, 0);
    ESP_LOGD(TAG, "successfully scrolled text down");
}

void DataView::displayText(char *text, SSD1306_t * dev) {
    int length = strlen(text);
    if(length <= 128 ){
        if(length <= 16){
            ssd1306_display_text(dev, 0, text, length, 0);
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
                    ssd1306_display_text(dev, page, newString, 16, 0);
                }
                else { //rest of string is not 16 long, so just copying what's left
                    char newLength = length-subIndexStart;
                    char newString[newLength];
                    for (signed char i = 0; i < newLength; i++){ //making the substring
                        newString[i] = text[subIndexStart+i];
                    }
                    ssd1306_display_text(dev, page, newString, newLength, 0);
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
            ssd1306_display_text(dev, page, subString, 16, 0);
        }
        ESP_LOGD(TAG, "successfully showing first part of long text, that fits on the display");
        vTaskDelay(1000);
        int subIndexStart = 128;
        char neededPages = ceil((double) (length-subIndexStart)/ (double) 16); //division by 16 could be bitshifting?
        for(char i = 0; i < neededPages-1; i++) {
            char newBottomString[16];
            for (signed char j = 0; j < 16; j++) {
                newBottomString[j] = text[subIndexStart+j];
            }
            subIndexStart += 16;
            scrollTextUp(dev, newBottomString, 16);
            vTaskDelay(10);
        }
        ESP_LOGD(TAG, "successfully scrolled text up and showing next full line of long text");
        signed char restLength = length-subIndexStart;
        char restString[restLength];
        for(signed char i = 0; i < restLength; i++) {
            restString[i] = text[subIndexStart+i];
        }
        scrollTextUp(dev, restString, restLength);
        ESP_LOGD(TAG, "successfully scrolled text up and showing last line of long text");
    }
}

//Draws text starting at the specified location, does not make you all text fits on screen.
//this method expects 0 <= x <= 127 and 0 <= y <= 63 but will not fail it not satisfied.
//If text is too long, then it overflows 1 pixel down, from the other side.
void DataView::drawTextAt(char x, char y, char * text, bool invert, SSD1306_t * dev) {
    /*char page = y >> 3; //integer division by 8
    char yOffset = y - (page << 3);
    ssd1306_display_text(dev, page, text, strlen(text), 0);
    for(char i = 0; i < yOffset; i++){
        ssd1306_wrap_arround(dev, SCROLL_DOWN, 0, 127, 0);
    }
    for(char i = 0; i < x; i++){
        ssd1306_wrap_arround(dev, SCROLL_RIGHT, 0, 63, 0); //scrolls once start at seg 0 and to seg 127 (the whole line)
    }*/
    int textLength = strlen(text);
    char offset = 0;
    for(int i = 0; i < textLength; i++){
        uint8_t * image = font8x8_basic_tr[(uint8_t) text[i]];
        for(signed char j = 0; j < 8; j++){
            uint8_t firstbyte  = image[j];
            for(signed char k = 0; k < 8; k++){
                char bit = firstbyte >> k & 1; //taking one bit at a time from the byte
                if(invert) bit = !bit;
                //if bit = 1, meaning it should be there (if no invert), then we add it.
                _ssd1306_pixel(dev, j+x+offset, k+y, !bit);
                vTaskDelay(1/1000);
            }
        }
        offset += 8;
    }
    ssd1306_show_buffer(dev);
    ESP_LOGD(TAG, "successfully displayed text at %d, %d", x, y);
}

void DataView::highlightRectangle(char x, char y, char length, char height, SSD1306_t * dev){
    for(char i = x; i <= length + x; i++){
        for(char j = y; j <= y + height; j++){
            _ssd1306_pixel(dev, i, j, 0);
            vTaskDelay(1/1000);
        }
    }
    ssd1306_show_buffer(dev);
    ESP_LOGD(TAG, "successfully displayed highlighted rectangle");
}

//is maybe not needed
void DataView::drawRectangle(char x, char y, char length, char height, SSD1306_t * dev){
    for(char i = x; i <= length + x; i++){
        _ssd1306_pixel(dev, i, y, 0);
        _ssd1306_pixel(dev, i, y + height, 0);
        vTaskDelay(1/1000);
    }
    for(char i = y + 1; i < y + height ; i++){
        _ssd1306_pixel(dev, x, i, 0);
        _ssd1306_pixel(dev, x+length, i, 0);
        vTaskDelay(1/1000);
    }
    ssd1306_show_buffer(dev);
    ESP_LOGD(TAG, "successfully displayed rectangle");
}

void DataView::scrollTableUp(SSD1306_t * dev, char * ID, char * name){
    char clearingString[] = "        ";
    for(char j = 0; j < 16; j++){
        ssd1306_wrap_arround(dev, SCROLL_UP, 0, 127, 0); //scrolls once start at seg 0 and to seg 127 (the whole line)
    }
    ssd1306_display_text(dev, 6, clearingString, strlen(clearingString), 0);
    drawTextAt(65, 48, clearingString, 0, dev);
    ssd1306_display_text(dev, 6, ID, strlen(ID), 0);
    drawTextAt(65, 48, name, 0, dev);
}

void DataView::scrollTableDown(SSD1306_t * dev, char * ID, char * name){
    char clearingString[] = "        ";
    for(char j = 0; j < 16; j++){
        ssd1306_wrap_arround(dev, SCROLL_DOWN, 0, 127, 0); //scrolls once start at seg 0 and to seg 127 (the whole line)
    }
    ssd1306_display_text(dev, 0, clearingString, strlen(clearingString), 0);
    drawTextAt(65, 0, clearingString, 0, dev);
    ssd1306_display_text(dev, 0, ID, strlen(ID), 0);
    drawTextAt(65, 0, name, 0, dev);
}

void DataView::drawIDTable(char IDs[32][8], char names[32][8], SSD1306_t * dev){
    drawTable(2, 4, dev);
    //fill the table
    signed char i;
    for(i = 0; i < 4; i++){
        ssd1306_display_text(dev, i*2, IDs[i], strlen(IDs[i]), 0);
        drawTextAt(65, i*16, names[i], 0, dev);
    }
    vTaskDelay(1000);
    //if everything doesn't fit on the table
    for(; i < 32; i ++) {
        if(strlen(IDs[i]) > 0){
            scrollTableUp(dev, IDs[i], names[i]);
            //vTaskDelay(1/1000);
        }
        else {
            break;
        }
    }
    ESP_LOGD(TAG, "successfully drew data Table");
}
//works for ID table
void DataView::highlightTableCell(char row, char column, char * text, SSD1306_t * dev){
    if(column){
        drawTextAt(65, row*16, text, 1, dev);
    }
    else{
        ssd1306_display_text(dev, row*2, text, strlen(text), 1);
    }
}