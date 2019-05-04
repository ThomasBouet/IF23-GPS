#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SD.h>
#include <ButtonsGPS.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

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

int currentState;
int isDoingSmth = 0;

ButtonsGPS btn;
//petit rappel : déclarer les fonctions avant la boucle loop
void battery();

TinyGPS gps;
const int GPS_RX = 3, GPS_TX = 2;
SoftwareSerial ss(GPS_TX, GPS_RX);

void setup() {
  Serial.begin(9600);
  ss.begin(4800);
  lcd.begin(8, 2);
  pinMode(pinBat, INPUT);
  currentState = BATTERY;
  Serial.println("Initialisation");
}

void loop() {
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }

  gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0)
    Serial.println("** No characters received from GPS: check wiring **");
  /*
  Serial.print("state before btn pressed ");
  Serial.println(titleMenu[currentState]);
  //maj de l'état
  int button = btn.readButtons();
  Serial.print("button ");
  Serial.println(button);
  Serial.print("state when btn pressed ");
  Serial.println(titleMenu[currentState]);
  switch (button) {
    case 1 :
    //état batterie par défaut
      currentState = 0;
      lcd.clear();
      break;
    case 2 :
      currentState++;
      if(currentState >= MENU_SIZE){
        currentState =  MENU_SIZE-1;
      }
      lcd.clear();
      break;
    case 3 :
      currentState--;
      if(currentState <= 0){
        currentState = 0;
      }
      lcd.clear();
      break;
    case 4 :
      isDoingSmth = 1;
      break;
  }

  // lcd.clear();
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
  Serial.print("state after btn pressed ");
  Serial.println(titleMenu[currentState]);*/
}

void battery(){
  lcd.setCursor(4, 1);
  tension = (float)(analogRead(pinBat))/1023.0*6.5;
  lcd.print(tension);
  lcd.setCursor(3, 1);
  lcd.print("V");
  if(btn.readButtons() == 4){
    lcd.clear();
    isDoingSmth = 0;
    return;
  }
}
