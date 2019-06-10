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
  ptDebug = 1;
  if (!SD.begin(SD_CS)) {
    //carte pas insérée, mauvais branchement, mauvais pin
    Serial.println("Probleme SD");
    isSdOk = false;

  } else {
   //Branchement correct et carte insérée
    Serial.println("SD ok");
    isSdOk = true;

  }
  isWriting = false;
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
      break;

  }

  // lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(titleMenu[currentState]);

  switch(currentState){
    case BATTERY :
      lcd.setCursor(4, 0);
      tension = (float)(analogRead(VBAT))/1023.0*6.5;
      lcd.print(tension);
      lcd.setCursor(0, 1);
      lcd.print("SD");
      lcd.setCursor(3, 1);
      if(isSdOk){
        lcd.print("Ok");
      }else{
        lcd.print("noOk");
      }
      break;

    case USB :
      lcd.setCursor(0,1);
      lcd.print(currentState);

      if(isDoingSmth == 1){
        int compteur = 1;
        int ligneCompteur = 1;
        sprintf(fileName, "Trajet%d.txt", compteur);
        while(SD.exists(fileName)){
          Serial.println(fileName);
          dFile = SD.open(fileName);

          if (dFile) {

            Serial.println("contenu :");
            // read from the file until there's nothing else in it:
            while (dFile.available()){
              Serial.write(dFile.read());
              ligneCompteur++;
              if(ligneCompteur%1000 == 0){ 
                while(btn.readButtons() != 4){
                  lcd.setCursor(0, 1);
                  lcd.print("p2c");
                }
              }
            }
            // close the file:
            dFile.close();

          } else Serial.println("Trajet.txt : error opening ");
          SD.remove(fileName);
          compteur++;
          sprintf(fileName, "Trajet%d.txt", compteur);
        }

        isDoingSmth = 0;
        fileIndex = 0;
      }
      break;

    case GPS_REC :
    lcd.setCursor(7, 0);

      if(!gps.satellites.isValid()) lcd.print("X");
      else lcd.print(gps.satellites.value());

      lcd.setCursor(0,1);

      if(!gps.location.isValid()) lcd.print("Srch sig");
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
  sprintf(&infos[strlen(infos)], "%d;", p);

  if(gps.location.isValid()){

    if(currentState == GPS_REC){

      lcd.setCursor(0,1);
      lcd.print("Sig fnd!");

    }

    locating = true;
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
  sprintf(fileName, "Trajet%d.txt", fileIndex);

  while(SD.exists(fileName) && !isWriting){

    fileIndex++;
    sprintf(fileName, "Trajet%d.txt", fileIndex);

  }

  /*if(SD.exists(NAME_FILE) && !isWriting){
    Serial.print("delet ");Serial.println(SD.remove(NAME_FILE));
    isWriting = true;
  }
  else{*/

    dFile = SD.open(fileName, FILE_WRITE);

    if(dFile){

      Serial.print(fileName);Serial.print(" c ");

    }else{

      Serial.print(fileName);Serial.println(" : ECHEC");

    }

    dFile.close();

    if(SD.exists(fileName) == true && !isWriting){

      isWriting = true;
      Serial.print(fileName);Serial.println(" e");
      dFile = SD.open(fileName, FILE_WRITE);

      if(dFile){

        Serial.println(infos);
        dFile.println(fileHeader);
        dFile.close();
        isWriting = true;

      }else{

        Serial.print(fileName);Serial.println(" : cECHEC");

      }
    }

    Serial.print("Point n° :");Serial.println(pt);
    displayInfo(pt);
    dFile = SD.open(fileName, FILE_WRITE);

    if(dFile){

      if(locating){
        Serial.println(infos);
        dFile.println(infos);
        pt++;
      }else Serial.println("Lat & Lng innvalid");  

    }else{

      Serial.print(fileName);Serial.println(" : oECHEC");

    }

    dFile.close();
//  }

  if(btn.readButtons()==4){
    isDoingSmth = 0;
    isWriting = false;
    pt = 0;
    lcd.setCursor(0, 1);
    lcd.print("        ");
  }
  delay(1000);
}

void refreshGPS(){

  while(ss.available() > 0)
    if(gps.encode(ss.read())){
      displayInfo(ptDebug);
      //Serial.print("debug : "); Serial.println(infos);
      ptDebug++;
    }

  if (millis() > 6000 && gps.charsProcessed() < 10){

    Serial.println(F("No GPS detected: check wiring"));
    while(true);

  }
}
