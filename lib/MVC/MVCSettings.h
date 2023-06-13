#ifndef FAGPROJEKTLORA2023_MVCSETTINGS_H
#define FAGPROJEKTLORA2023_MVCSETTINGS_H

//keyboard definitions
#define UP_KEY 'w'//0
#define RIGHT_KEY 'd'//1
#define LEFT_KEY 'a'//2
#define DOWN_KEY 's'//3
#define ENTER_KEY 'v'//4
#define BACK_KEY 'b'//5

//state definitions
#define START_STATE 0
#define COMPASS_STATE 1
#define TABLE_STATE 2
#define NAV_OVERVIEW_STATE 3

//pins for setup of i2c with display
#define CONFIG_SDA_GPIO 21
#define CONFIG_SCL_GPIO 22
#define CONFIG_RESET_GPIO 15

#define MAX_NUMBER_OF_MEMBERS 127
#define MEMBER_CIRCLE_SIZE 3

#endif // FAGPROJEKTLORA2023_MVCSETTINGS_H
