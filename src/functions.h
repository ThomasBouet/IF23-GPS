#include <initialisation.h>
#include <ButtonsGPS.h>

//setup
void initProject(){
  Serial.begin(9600);
  ss.begin(4800);
  lcd.begin(8, 2);
  pinMode(VBAT, INPUT);
  currentState = BATTERY;
  fileIndex = 1;
  pt = 1;

  if (!SD.begin(SD_CS)) {
      //carte pas insérée, mauvais branchement, mauvais pin
      Serial.println("Carte mal insérée/Mauvais branchement/Mauvais pin");
    } else {
      //Branchement correct et carte insérée
      Serial.println("Branchement correct et carte insérée");
    }
}

void battery(){
  lcd.setCursor(4, 1);
  tension = (float)(analogRead(VBAT))/1023.0*6.5;
  lcd.print(tension);
  lcd.setCursor(3, 1);
  lcd.print("V");
  if(btn.readButtons() == 4){
    lcd.clear();
    isDoingSmth = 0;
  }
}

void readRun(){
  int i = 1;
  String str = i+".txt";
  /*while(sdCard.existingFile(str) == 1){
    sdCard.readFile(str);
    i++;
    str = i+".txt";
  }
  if(sdCard.existingFile(str) == 0){
    Serial.println("Tous les fichiers parcourus");
    lcd.setCursor(0,1);
    lcd.print("Fin");
  }*/
}


String printDateTime()
{
  String str = "";
  if (gps.time.isValid()){
          if (gps.time.hour() < 10) str += "0";
          str += String(gps.time.hour()+2) + ":";
          if (gps.time.minute() < 10) str += "0";
          str += String(gps.time.minute()) + ":";
          if (gps.time.second() < 10) str += "0";
          str += String(gps.time.second());
          str += ";";
        }
        else{
          str += "TIME INVALID;";
}
  return str;
}

String displayInfo(int p)
{
  String str = "Point"+String(p)+";";
  if(gps.location.isValid()){
    str += String(gps.location.lat(), 6)+";";
    str += String(gps.location.lng(), 6)+";";
  }else{
    str += "LAT INVALID;LNG INVALID;";
  }

  if(gps.altitude.isValid()){
    str += String(gps.altitude.meters(), 2)+";";
  }else{
    str += "ALT INVALID;";
  }

  str += printDateTime();

  if(gps.hdop.isValid()){
    str += String(gps.hdop.hdop(), 1)+";";
  }else{
    str += "HDOP INVALID;";
  }

  if(gps.satellites.isValid()){
    str += String(gps.satellites.value())+";";
  }else{
    str += "SAT INVALID;";
  }

  return str;
}

void gpsLocation(){
  lcd.setCursor(0, 1);
  lcd.print("Wait sig");
  String file = String(fileIndex)+".txt";
  if(!isWriting){
    while(SD.exists(file)){
      fileIndex++;
      file = String(fileIndex)+".txt";
    }
    dFile = SD.open(file, FILE_WRITE);
    if(dFile){
      Serial.println(String(file)+" a été créé");
    }else{
      Serial.println(String(file)+" : ECHEC");
    }
    dFile.close();
    if(SD.exists(file) == 1){
      isWriting = true;
      Serial.println(file);
      //sdCard.writeFile(file, file);
      dFile = SD.open(file, FILE_WRITE);
      if(dFile){
        dFile.println(file);
        dFile.println("Latitude,Longitude,Altitude,Date,HDOP,Satellites");
      }else{
        Serial.println(String(file)+" : ECHEC");
      }
      dFile.close();
    }
  }else{
    file = String(fileIndex)+".txt";
    String content = displayInfo(pt);
    Serial.println(content);
    dFile = SD.open(file, FILE_WRITE);
    if(dFile){
      dFile.println(content);
      pt++;
    }else{
      Serial.println(String(file)+" : ECHEC");
    }
    dFile.close();
  }
}

void refreshGPS(){
  while(ss.available() > 0)
    if(gps.encode(ss.read())){
      Serial.print("debug : "); Serial.println(displayInfo(pt));
      pt++;
    }
  if (millis() > 6000 && gps.charsProcessed() < 10){
    Serial.println(F("No GPS detected: check wiring"));
    while(true);
  }
}
