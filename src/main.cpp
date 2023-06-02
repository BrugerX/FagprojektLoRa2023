#include <Arduino.h>
#include <ssd1306.h>
#include "../lib/MVC/DataView.h"
#include "../lib/MVC/DataController.h"
#include "../lib/MVC/MVCSettings.h"

DataView dataView = DataView();
DataController dataController = DataController(dataView);
SSD1306_t dev;
char names[6][8] = {"Bjarke", "Benny", "Birger", "Bjarne", "Bent", "Birk"};

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    delay(2000);
    //Serial.println("Hello world");
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    //initializing display of size 128x64
    ssd1306_init(&dev, 128, 64);
    ssd1306_contrast(&dev, 0xc3);
    ssd1306_clear_screen(&dev, false);

    //dataView.drawCompass(&dev);
    //dataController.handleUserInput(UP_KEY, &dev);
    dataController.handleUserInput(LEFT_KEY, &dev); //to initialise startscreen
    //Serial.print((int) dataController.getModelState());

    for(int i = 0; i < 6; i++){
        dataController.addGroupMember(Member(names[i],NavigationData()));
    }
    Serial.println("Test beginning");
    char s[] = "Name";
    Member m1 = Member(s,NavigationData());
    Member m2 = Member(s,NavigationData());
    bool result = m1 == m2;
    Serial.println("The result is: ");
    Serial.println(result,DEC);
    /*while(Serial.available() != 0){
      char input = Serial.read();
      delay(2);
      if(input == 'g'){
        char IDs[32][8] = {"ID1", "ID2", "ID3", "ID4", "ID5", "ID6", "ID7", "ID8"};
        char names[32][8] = {"Name1", "Name2", "Name3", "Name4", "Name5", "Name6", "Name7", "Name8"};
        dataView.drawIDTable(IDs, names, &dev);
      }
    }*/
}
char input = ' ';
void loop() {
    // put your main code here, to run repeatedly:
    if(Serial.available() != 0){
        Serial.println("Ready to read");
        input = (char) Serial.read();
        Serial.print("char is: " );
        Serial.println(input);
        dataController.handleUserInput(input, &dev);
   }
}