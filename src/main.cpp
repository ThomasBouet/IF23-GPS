#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "ButtonsGPS.h"
#include <SD.h>



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

ButtonsGPS btn;



void setup() {
  Serial.begin(9600);

  pinMode(pinBat, INPUT);


  lcd.begin(8, 2);
  //lcd.noDisplay();
  //lcd.display();

}




void loop() {


  //Prend en compte la différence entre le 3.3V d'Arduino et le 3.25V Max de la batterie
  //tension = (float(analogRead(pinBat))/1007.0)*6.5;
  tension = (float)(analogRead(pinBat))/1023.0*6.5;
  lcd.setCursor(0, 1);
  lcd.print(tension);




  lcd.setCursor(0, 0);
  lcd.print(btn.readButtons());



}
