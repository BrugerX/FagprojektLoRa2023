#include <ssd1306.h>
#include "Settings.h"
#include "CompassViewer.h"
#include "TableViewer.h"
#include "../lib/ssd1306/ssd1306.h"
#include <vector>
#include "Member.h"


using namespace std;


#ifndef DATAVIEW_H
#define DATAVIEW_H


class DataView {
private:
    NavigationViewer compassViewer;
    TableViewer tableViewer;
    void scrollTextUp(SSD1306_t * dev, char * text, char length);
    void scrollTextDown(SSD1306_t * dev, char * text, char length);

public:
    DataView();
    void drawCircle(int xCenter, int yCenter, int r, SSD1306_t * dev);
    void highlightCircle(int xCenter, int yCenter, int r, SSD1306_t * dev);
    void drawCompass(SSD1306_t * dev);
    void displayText(char *text, SSD1306_t * dev);
    void drawTextAt(char x, char y, char *text, char length, bool invert, SSD1306_t *dev);
    void highlightRectangle(char x, char y, char length, char height, SSD1306_t * dev);
    void drawRectangle(char x, char y, char length, char height, SSD1306_t * dev);
    void drawIDTable(char startIndex, vector<Member> members, SSD1306_t * dev);
    void highlightTableCell(char row, char column, char * text, char highlight, SSD1306_t * dev);
    void drawTable(char columns, char rows, SSD1306_t * dev);
    void scrollTableUp(SSD1306_t * dev, char * ID, char * name);
    void scrollTableDown(SSD1306_t * dev, char * ID, char * name);
};
#endif //DATAVIEW_H
