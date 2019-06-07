#include <Arduino.h>
#include <initialisation.h>

void setup() {

  //initialisation des ports séries
  Serial.begin(9600);
  ss.begin(4800);
  lcd.begin(8, 2);
  //initialisation des éléements de surveillance de la batterie
  pinMode(VBAT, INPUT);
  currentState = BATTERY;
  //initialisation du compteur de points pris par le gps
  pt = 1;

  if (!SD.begin(SD_CS)) {
    //carte pas insérée, mauvais branchement, mauvais pin
    Serial.println("Probleme SD");

  } else {
   //Branchement correct et carte insérée
    Serial.println("SD ok");

  }
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
      if(currentState >= MENU_SIZE) currentState =  MENU_SIZE-1;
      lcd.clear();
      break;

    case 3 :
      currentState--;
      if(currentState <= 0) currentState = 0;
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
      lcd.setCursor(1, 1);
      tension = (float)(analogRead(VBAT))/1023.0*6.5;
      lcd.print(tension);
      lcd.setCursor(0, 1);
      lcd.print("V");
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

        Serial.println(NAME_FILE);
        dFile = SD.open(NAME_FILE);

        if (dFile) {

          Serial.println("contenu :");
          // read from the file until there's nothing else in it:
          while (dFile.available()) Serial.write(dFile.read());
          // close the file:
          dFile.close();

        } else Serial.println("Trajet.txt : error opening ");

        isDoingSmth = 0;

      }
      break;

    case GPS_REC :
      lcd.setCursor(0,1);
      lcd.print(currentState);
      if(isDoingSmth == 1) gpsLocation();
      break;

  }

refreshGPS();
  //maj de l'état
  delay(10);
}


void printDateTime(){

  if (gps.time.isValid()){

    if (gps.time.hour() < 10) sprintf(&infos[strlen(infos)], "%s", "0");

    sprintf(&infos[strlen(infos)], "%d:", gps.time.hour()+2);

    if (gps.time.minute() < 10) sprintf(&infos[strlen(infos)], "%s", "0");

    sprintf(&infos[strlen(infos)], "%d:", gps.time.minute());

    if (gps.time.second() < 10) sprintf(&infos[strlen(infos)], "%s", "0");

    sprintf(&infos[strlen(infos)], "%d;", gps.time.second());

  }else sprintf(&infos[strlen(infos)], "%s", "TIME INVALID;");
}

void displayInfo(int p){

  memset(infos, 0, sizeof infos);
  sprintf(&infos[strlen(infos)], "Point%d;", p);

  if(gps.location.isValid()){

    dtostrf(gps.location.lat(), 3, 6, &infos[strlen(infos)]);
    sprintf(&infos[strlen(infos)], "%s", ";");
    dtostrf(gps.location.lng(), 3, 6, &infos[strlen(infos)]);
    sprintf(&infos[strlen(infos)], "%s", ";");

  }else sprintf(&infos[strlen(infos)], "%s", "LAT INV;LNG INV;");

  if(gps.altitude.isValid()){

    dtostrf(gps.altitude.meters(), 4, 6, &infos[strlen(infos)]);
    sprintf(&infos[strlen(infos)], "%s", ";");

  }else sprintf(&infos[strlen(infos)], "%s", "ALT INVALID;");

  printDateTime();

  if(gps.hdop.isValid()){

    dtostrf(gps.hdop.hdop(), 3, 3, &infos[strlen(infos)]);
    sprintf(&infos[strlen(infos)], "%s", ";");

  }else sprintf(&infos[strlen(infos)], "%s", "ALT INVALID;");

  if(gps.satellites.isValid()) sprintf(&infos[strlen(infos)], "%d;", gps.satellites.value());
  else sprintf(&infos[strlen(infos)], "%s","SAT INVALID;");
}

void gpsLocation(){

  lcd.setCursor(0, 1);
  lcd.print("Wait sig");

  if(SD.exists(NAME_FILE)){
    Serial.print("delet ");Serial.println(SD.remove(NAME_FILE));
  }
  else{

    dFile = SD.open(NAME_FILE, FILE_WRITE);

    if(dFile){

      Serial.print(NAME_FILE);Serial.println("c");

    }else{

      Serial.print(NAME_FILE);Serial.println(" : ECHEC");

    }

    dFile.close();

    if(SD.exists(NAME_FILE) == true){

      isWriting = true;
      Serial.print(NAME_FILE);Serial.println(" e");
      dFile = SD.open(NAME_FILE, FILE_WRITE);

      if(dFile){

        Serial.println(infos);
        dFile.println(lineTitle);
        dFile.close();

      }else{

        Serial.print(NAME_FILE);Serial.println(" : cECHEC");

      }
    }


    displayInfo(pt);
    dFile = SD.open(NAME_FILE, FILE_WRITE);
    Serial.println(dFile);

    if(dFile){

      dFile.println(infos);
      pt++;
      delay(1000);

    }else Serial.print(NAME_FILE);Serial.println(" : oECHEC");

    dFile.close();
  }

  if(btn.readButtons()==4) isDoingSmth = 0;

}

void refreshGPS(){

  while(ss.available() > 0)
    if(gps.encode(ss.read())){
      /*displayInfo(pt);
      Serial.print("debug : "); Serial.println(infos);
      pt++;*/
    }

  if (millis() > 6000 && gps.charsProcessed() < 10){

    Serial.println(F("No GPS detected: check wiring"));
    while(true);

  }
}
