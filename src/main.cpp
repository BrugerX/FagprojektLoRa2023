#include <Arduino.h>
#include <ssd1306.h>
#include "../lib/MVC/DataView.h"
#include "../lib/MVC/DataController.h"
#include "../lib/MVC/MVCSettings.h"
#include <cstdlib>

DataView dataView = DataView();
DataController dataController = DataController(&dataView);
SSD1306_t dev;
char names[6][8] = {"Bjarke", "Benny", "Birger", "Bjarne", "Bent", "Birk"};

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    delay(2000);
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    //initializing display of size 128x64
    ssd1306_init(&dev, 128, 64);
    ssd1306_contrast(&dev, 0xc3);
    ssd1306_clear_screen(&dev, false);

    dataView.showStartScreen(&dev); //to initialise start screen

    for(int i = 0; i < 6; i++){
        srand(i);
        dataController.addGroupMember(Member(names[i], NavigationData()));
    }
    /*while(Serial.available() != 0){
      char input = Serial.read();
      delay(2);
      if(input == 'g'){
        char IDs[32][8] = {"ID1", "ID2", "ID3", "ID4", "ID5", "ID6", "ID7", "ID8"};
        char names[32][8] = {"Name1", "Name2", "Name3", "Name4", "Name5", "Name6", "Name7", "Name8"};
        dataViewet.drawIDTable(IDs, names, &dev);
      }
    }*/
}
char input = ' ';
void loop() {
    // put your main code here, to run repeatedly:
    if(Serial.available() != 0){
        Serial.println("Ready to read");
        input = (char) Serial.read();
        if(input != 10){
            Serial.print("char is: " );
            Serial.println(input);
            dataController.handleUserInput(input, &dev);
        }
   }
}