#include <Arduino.h>
#include <Wire.h>
#include <functions.h>

void setup() {
  initProject();
}

void loop() {
  //maj de l'état
  int button = btn.readButtons();
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
      /*if (isDoingSmth == 1){
        Serial.println("Dans ma sd il y a :");
        sdCard.printDirectory(sdCard.getRoot(), 0);
      }*/
      break;
    case USB :
      lcd.setCursor(0,1);
      lcd.print(currentState);
      break;
    case GPS_REC :
      lcd.setCursor(0,1);
      lcd.print(currentState);
      if(isDoingSmth == 1){
        gpsLocation();
      }
      break;
  }
}
