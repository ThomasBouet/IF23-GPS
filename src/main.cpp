#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SD.h>
#include <ButtonsGPS.h>
#include "menu.h"

//Carte SD
#define pinSD A0
Sd2Card card;
SdVolume volume;
SdFile root;

//Control tension
#define pinBat 14
float tension;

//LCD
const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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

ButtonsGPS btn;
//petit rappel : déclarer les fonctions avant la boucle loop
void battery(){
  lcd.setCursor(4, 1);
  tension = (float)(analogRead(pinBat))/1023.0*6.5;
  lcd.print(tension);
  lcd.setCursor(3, 1);
  lcd.print("V");

  if(btn.readButtons() != 0){
    isDoingSmth = 0;
    lcd.setCursor(3, 1);
    lcd.print("     ");
    return;
  }

}

void setup() {
  Serial.begin(9600);
  lcd.begin(8, 2);
  pinMode(pinBat, INPUT);
  currentState = BATTERY;
  button = 0;
}

void loop() {
  Serial.print("Current State :");Serial.println(titleMenu[currentState]);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(titleMenu[currentState]);

  switch(currentState){
    case BATTERY :
      lcd.setCursor(0,1);
      lcd.print(currentState);
      if(isDoingSmth == 1){
        battery();
      }
      break;
    case SD_SIZE :
      lcd.setCursor(0,1);
      lcd.print(currentState);
      break;
    case SD_FORM :
      lcd.setCursor(0,1);
      lcd.print(currentState);
      break;
    case USB :
      lcd.setCursor(0,1);
      lcd.print(currentState);
      break;
    case GPS_REC :
      lcd.setCursor(0,1);
      lcd.print(currentState);
      break;
  }

  Serial.println(titleMenu[currentState]);
  switch (btn.readButtons()) {
    case 1 :
      //état batterie par défaut
      currentState = 0;
      // lcd.clear();
      break;
    case 2 :
      currentState++;
      if(currentState >= MENU_SIZE){
        currentState =  MENU_SIZE-1;
      }
      // lcd.clear();
      break;
    case 3 :
      currentState--;
      if(currentState <= 0){
        currentState = 0;
      }
      // lcd.clear();
      break;
    case 4 :
      isDoingSmth = 1;
      break;
  }
}
