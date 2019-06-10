//#include <Wire.h>
#include <LiquidCrystal.h>
#include <ButtonsGPS.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include <SD.h>
//pin
#define GPS_TX 2
#define GPS_RX 3
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
File dFile;
int fileIndex;
bool isWriting;

//buttons
ButtonsGPS btn;

//menu
const int BATTERY = 0, USB = 1, GPS_REC = 2;
const int MENU_SIZE = 3;
const int navMenu [] = {
  BATTERY, USB, GPS_REC
};
const char title1[4] = "Bat";
const char title2[4] = "USB";
const char title3[4] = "GPS";
const char * titleMenu [] = {
  title1, title2, title3
};
int button;
int currentState;
int isDoingSmth = 0;

//battery
float tension;

//GPS
TinyGPSPlus gps;
SoftwareSerial ss(GPS_RX, GPS_TX);
int pt;
int ptDebug;
char infos[66];
char fileName[13] = "Trajet";
const char fileHeader[56] = "Point;Latitude;Longitude;Altitude;Date;HDOP;Satellites;";
bool locating;

//SD
bool isSdOk;

//fonctions
void refreshGPS();
void gpsLocation();
