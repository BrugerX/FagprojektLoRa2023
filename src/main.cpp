#include <Arduino.h>
#include <ssd1306.h>
#include <DataView.h>
#include <DataController.h>
#include "settings.h"

#define CONFIG_SDA_GPIO 21
#define CONFIG_SCL_GPIO 22
#define CONFIG_RESET_GPIO 15

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    //delay(2000);
    //Serial.println("Hello world");
    SSD1306_t dev;
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    //initializing display of size 128x64
    ssd1306_init(&dev, 128, 64);
    ssd1306_contrast(&dev, 0xc3);
    ssd1306_clear_screen(&dev, false);

    DataView dataView;
    //dataView.drawCompass(&dev);
    DataController dataController = DataController(dataView);
    dataController.handleUserInput(UP_KEY, &dev);
    dataController.handleUserInput(LEFT_KEY, &dev);
    //Serial.print((int) dataController.getModelState());
    //char startText[] = "StartScreen";
    //ssd1306_clear_screen(&dev, 0);
    //ssd1306_display_text(&dev, 4, startText, strlen(startText), 0);

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

void loop() {
    // put your main code here, to run repeatedly:
    //Serial.print("ABC");
}