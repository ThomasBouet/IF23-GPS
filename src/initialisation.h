#include <LiquidCrystal.h>
#include <SD.h>
#include <ButtonsGPS.h>
#include <ProjectGPS.h>

//pin
/*
#define GPS_TX 2
#define GPS_RX 3
*/
#define LCD_RS 4
#define LCD_E 5
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9
#define SD_CS 10
#define SD_MOSI 11
#define SD_MISO 12
#define SD_SCK 13
#define VBAT 14
/*
#define BP1 15
#define BP0 16
#define BPEN 17
*/

//lcd
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//sd
Sd2Card card;
SdVolume volume;
SdFile root;

//buttons
ButtonsGPS btn;

//menu
const int BATTERY = 0, SD_SIZE = 1, SD_FORM = 2, USB = 3, GPS_REC = 4;
const int MENU_SIZE = 5;
const int navMenu [] = {
  BATTERY, SD_SIZE, SD_FORM, USB, GPS_REC
};
const String titleMenu [] = {
  "Battery", "SD_Size", "SD_Form", "USB", "GPS_Rec"
};
int button;
int currentState;
int isDoingSmth = 0;

//battery
float tension;

//GPS
ProjectGPS pgps;
