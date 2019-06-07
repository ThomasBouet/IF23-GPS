#include <initialisation.h>

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
  String str = "Trajet.txt";
  Serial.println(str);
  dFile = SD.open(str);
  if (dFile) {
    Serial.println("contenu :");
    // read from the file until there's nothing else in it:
    while (dFile.available()) {
      Serial.write(dFile.read());
    }
    // close the file:
    dFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("Trajet.txt : error opening ");
  }
  isDoingSmth = 0;
}


String printDateTime()
{
  String str = "";
  if (gps.time.isValid()){

    if (gps.time.hour() < 10) str += "0";
    str += String(gps.time.hour()+2);
    str += ":";
    if (gps.time.minute() < 10) str += "0";
    str += String(gps.time.minute());
    str += ":";
    if (gps.time.second() < 10) str += "0";
    str += String(gps.time.second());  

  }else{

    str += "TIME INVALID";

  }

  str += ";";
  return str;

}

String displayInfo(int p){
  String str = "Point";
  Serial.println(str);
  if(gps.location.isValid()){

    str += String(gps.location.lat(), 6);
    str += ";";
    str += String(gps.location.lng(), 6);

  }else{
    str += "LAT INVALID;LNG INVALID";

  }
  Serial.println(str);
  str += ";";
  Serial.println(str);
  if(gps.altitude.isValid()){

    str += String(gps.altitude.meters(), 2);

  }else{
    str += "ALT INVALID";

  }
  Serial.println(str);
  str += ";";
  Serial.println(str);
  str += printDateTime();
  Serial.println(str);
  if(gps.hdop.isValid()){
   
    str += String(gps.hdop.hdop(), 6);

  }else{

    str += "HDOP INVALID";

  }
  Serial.println(str);
  str += ";";
  Serial.println(str);
  if(gps.satellites.isValid()){

    str += String(gps.satellites.value(), 6);

  }else{

    str += "SAT INVALID";

  }
  Serial.println(str);
  str += ";";
  Serial.println(str);
  return str;
}

void gpsLocation(){
  lcd.setCursor(0, 1);
  lcd.print("Wait sig");
  String file = "Trajet.txt";
  Serial.println(file);
  if(SD.exists(file)){

    dFile = SD.open(file, FILE_WRITE);

    if(dFile){

      Serial.print(file);Serial.println(" a été créé");

    }else{

      Serial.print(file);Serial.println(" : ECHEC");

    }

    dFile.close();

    if(SD.exists(file) == true){

      isWriting = true;
      Serial.print(file);Serial.println(" exist");
      dFile = SD.open(file, FILE_WRITE);

      if(dFile){

        dFile.println(file);
        dFile.println("Latitude,Longitude,Altitude,Date,HDOP,Satellites");
        dFile.close();

      }else{

        Serial.print(file);Serial.println(" : ECHEC de la création");

      }
    }
  }else{

    String content = displayInfo(pt);
    Serial.println("working ?");
    dFile = SD.open(file, FILE_WRITE);
    Serial.println(dFile);
    if(dFile){

      dFile.println(content);
      pt++;
      delay(1000);
      

    }else{

      Serial.print(file);Serial.println(" : ECHEC de l'ouverture");

    }
    dFile.close();
  }
  if(btn.readButtons()==4){
    isDoingSmth = 0;
  }
}

void refreshGPS(){
  while(ss.available() > 0)
    if(gps.encode(ss.read())){
      //String ct = displayInfo(pt);
      //Serial.print("debug : "); Serial.println(ct);
      //pt++;
    }

  if (millis() > 6000 && gps.charsProcessed() < 10){

    Serial.println(F("No GPS detected: check wiring"));
    while(true);

  }
}
