#include <ssd1306.h>
#include "MVCSettings.h"
#include "../ssd1306/ssd1306.h"
#include <vector>
#include "Member.h"


using namespace std;


#ifndef DATAVIEW_H
#define DATAVIEW_H


class DataView {
private:
    SSD1306_t dev;

public:
    DataView();
    void initialiseView();
    void clearScreen();
    void showStartScreen();
    void drawTextAt(char x, char y, char *text, char length, bool invert);

    void drawCircle(int xCenter, int yCenter, int r);
    void highlightCircle(int xCenter, int yCenter, int r);
    void drawCompass();
    void drawMembersOnCompass(vector<Member> & members);

    void scrollTextUp(char * text, char length);
    void scrollTextDown(char * text, char length);
    void displayText(char *text);

    void drawTable(char columns, char rows);
    void drawIDTable(char startIndex, vector<Member> & members);
    void highlightTableCell(char row, char column, char * text, char highlight);
    void scrollTableUp(char * ID, char * timestamp);
    void scrollTableDown(char * ID, char * timestamp);

    void displayNavOverview(char x, char y, bool highlighted);
    void updateNavOverview(bool highlighted);
};
#endif // DATAVIEW_H
