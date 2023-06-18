#include <Arduino.h>
#include <ssd1306.h>
#include "../lib/MVC/DataView.h"
#include "../lib/MVC/DataController.h"
#include "../lib/MVC/MVCSettings.h"
#include <cstdlib>

DataView dataView = DataView();
DataController dataController = DataController(&dataView);
char names[6][8] = {"Bjarke", "Benny", "Birger", "Bjarne", "Bent", "Birk"};

void setup() {
    Serial.begin(9600);
    delay(2000);
    dataView.initialiseView();

    dataView.showStartScreen(); //to initialise start screen

    for(int i = 0; i < 6; i++){
        srand(i);
        dataController.addGroupMember(Member(names[i], NavigationData()));
    }
}
char input = ' ';
void loop() {
    if(Serial.available() != 0){
        Serial.println("Ready to read");
        input = (char) Serial.read();
        if(input != 10){
            Serial.print("char is: " );
            Serial.println(input);
            dataController.handleUserInput(input);
        }
   }
}