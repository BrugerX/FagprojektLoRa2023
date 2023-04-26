#include <Arduino.h>
#include <ssd1306.h>
#include <DataView.h>

#define CONFIG_SDA_GPIO 21
#define CONFIG_SCL_GPIO 22
#define CONFIG_RESET_GPIO 15

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    /*delay(2000);
    Serial.println("Hello world");
    SSD1306_t dev;
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    //initializing display of size 128x64
    ssd1306_init(&dev, 128, 64);
    ssd1306_contrast(&dev, 0xff);
    ssd1306_clear_screen(&dev, false);

    DataView dataView;
    dataView.drawCompass(&dev);*/

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
    Serial.print("ABC");
}