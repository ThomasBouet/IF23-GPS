#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SD.h>

<<<<<<< HEAD

//Menu
const int SYSTEM = 0, GPS = 1, STATS = 2;

const int BATTERY = 4, SDCARD = 5, USB = 3;

const int SDSIZE = 6, FORMAT = 7;

const int PARCOURS = 8, RECORD = 9;

const int TOTAL = 10, PARCOURS_CHOICE = 11;

//Tableau dont l'index est le currentState et l'état vers lequel mène chacun des boutons (1,2,3,4)
const int state[][4]={
  //SYSTEM ok
  {SYSTEM, STATS, GPS, BATTERY},
  //GPS ok
  {GPS, SYSTEM, STATS, PARCOURS},
  //STATS ok
  {STATS, GPS, SYSTEM, TOTAL},


  //BATTERY
  {SYSTEM, USB, SDCARD, BATTERY},
  //SDCARD
  {SYSTEM, BATTERY, USB, SDSIZE},
  //USB
  {SYSTEM, SDCARD, BATTERY, USB},


  //SDSIZE
  {SDCARD, FORMAT, FORMAT, SDSIZE},
  //FORMAT
  {SDCARD, SDSIZE, SDSIZE, FORMAT},


  //PARCOURS
  {GPS, RECORD, RECORD, PARCOURS},
  //RECORD
  {GPS, PARCOURS, PARCOURS, RECORD},


  //TOTAL
  {STATS, PARCOURS_CHOICE, PARCOURS_CHOICE, TOTAL},
  //PARCOURS_CHOICE
  {STATS, TOTAL, TOTAL, PARCOURS_CHOICE}
};


//Carte SD
#define pinSD A0
Sd2Card card;
SdVolume volume;
SdFile root;
=======
#include "ButtonsGPS.h"
#include "CardSD.h"
>>>>>>> a22d69ef1eeb9ab004a06c4adb8778fb7c69d71b

//Control tension
#define pinBat 14
float tension;

//LCD
const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

ButtonsGPS btn;

<<<<<<< HEAD
int currentState;

=======
>>>>>>> a22d69ef1eeb9ab004a06c4adb8778fb7c69d71b
void setup() {
  Serial.begin(9600);

  pinMode(pinBat, INPUT);

  lcd.begin(8, 2);

  currentState = SYSTEM;
}

<<<<<<< HEAD





void loop() {


  //AFFICHAGE TENSION
  //Prend en compte la différence entre le 3.3V d'Arduino et le 3.25V Max de la batterie
  //tension = (float(analogRead(pinBat))/1007.0)*6.5;
  // tension = (float)(analogRead(pinBat))/1023.0*6.5;
  // lcd.setCursor(0, 1);
  // lcd.print(tension);
  //
  //
  //
  // //AFFICHAGE VALEUR BOUTON
  // lcd.setCursor(0, 0);
  // lcd.print(btn.readButtons());



  //Print current state
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (currentState) {
    case SYSTEM:
      lcd.print("System");
      break;
    case GPS:
      lcd.print("GPS");
      break;
    case STATS:
      lcd.print("Stats");
      break;


    case BATTERY:
      lcd.print("Battery");
      break;
    case SDCARD:
      lcd.print("SD card");
      break;
    case USB:
      lcd.print("USB");
      break;


    case SDSIZE:
      lcd.print("Size");
      break;
    case FORMAT:
      lcd.print("Format");
      break;


    case PARCOURS:
      lcd.print("Parcours");
      break;
    case RECORD:
      lcd.print("Record");
      break;


    case TOTAL:
      lcd.print("Total");
      break;
    case PARCOURS_CHOICE:
      lcd.print("Parcours");
      break;
    }

    int button = (btn.readButtons()-1);
    //int etat = currentState;
    lcd.setCursor(0, 1);
    lcd.print(button);

    currentState = state[currentState][button];

=======
void loop() {

  //Prend en compte la différence entre le 3.3V d'Arduino et le 3.25V Max de la batterie
  //tension = (float(analogRead(pinBat))/1007.0)*6.5;
  tension = (float)(analogRead(pinBat))/1023.0*6.5;
  lcd.setCursor(0, 1);
  lcd.print(tension);

  lcd.setCursor(0, 0);
  lcd.print(btn.readButtons());
>>>>>>> a22d69ef1eeb9ab004a06c4adb8778fb7c69d71b

}
