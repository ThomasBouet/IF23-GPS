#include <Arduino.h>
#include <functions.h>

void setup() {
  Serial.begin(9600);
  ss.begin(4800);
  lcd.begin(8, 2);
  pinMode(VBAT, INPUT);
  currentState = BATTERY;
  pt = 1;
  if (!SD.begin(SD_CS)) {
    //carte pas insérée, mauvais branchement, mauvais pin
    Serial.println("Carte mal insérée/Mauvais branchement/Mauvais pin");
  } else {
   //Branchement correct et carte insérée
    Serial.println("Branchement correct et carte insérée");
  }
  char str[10] = "string";
  float truc = 12.34;
  dtostrf(truc, 2, 1, str);
 
  Serial.println(str);
}

void loop() {
  
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
      pt = 0;
      break;
  }

  // lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(titleMenu[currentState]);

  switch(currentState){
    case BATTERY :
      lcd.setCursor(0,1);
      lcd.print(currentState);
      battery();
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
      if(isDoingSmth == 1){
        readRun();
      }
      break;
    case GPS_REC :
      lcd.setCursor(0,1);
      lcd.print(currentState);
      if(isDoingSmth == 1){
        gpsLocation();
      }
      break;
  }
refreshGPS();
  //maj de l'état
  delay(10);
}
