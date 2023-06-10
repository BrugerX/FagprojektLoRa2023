#include <ssd1306.h>
#include "MVCSettings.h"
#include "CompassViewer.h"
#include "TableViewer.h"
#include "../ssd1306/ssd1306.h"
#include <vector>
#include "Member.h"


using namespace std;


#ifndef DATAVIEW_H
#define DATAVIEW_H


class DataView {
private:
    NavigationViewer compassViewer;
    TableViewer tableViewer;
    SSD1306_t dev;
    void scrollTextUp(char * text, char length);
    void scrollTextDown(char * text, char length);

public:
    DataView();
    void initialiseView();
    void clearScreen();
    void drawCircle(int xCenter, int yCenter, int r);
    void highlightCircle(int xCenter, int yCenter, int r);
    void drawCompass();
    void displayText(char *text);
    void drawTextAt(char x, char y, char *text, char length, bool invert);
    void highlightRectangle(char x, char y, char length, char height);
    void drawRectangle(char x, char y, char length, char height);
    void drawIDTable(char startIndex, vector<Member> & members);
    void highlightTableCell(char row, char column, char * text, char highlight);
    void drawTable(char columns, char rows);
    void scrollTableUp(char * ID, char * timestamp);
    void scrollTableDown(char * ID, char * timestamp);
    void showStartScreen();
    void displayNavOverview(char x, char y, bool highlighted);
    void updateNavOverview(bool highlighted);
    void drawMembersOnCompass(vector<Member> & members);
};
#endif //DATAVIEW_H
