#include "ProjectGPS.h"

#define GPS_TX 2
#define GPS_RX 3

SoftwareSerial ss(GPS_TX, GPS_RX);

ProjectGPS::ProjectGPS(){
  ss.begin(4800);
}

void ProjectGPS::getLocation()
{
  unsigned long chars;
  Serial.println(ss.isListening());
  while (ss.available()){
    Serial.println("truc");
    char c = ss.read();
    //
    Serial.write(c);
    while (!gps.encode(c)){
      Serial.write(c);
      Serial.println("Trame incomplète");
    }
  }
  Serial.println("J'ai une trame complète");
  //return displayInfo();
}

String ProjectGPS::displayInfo()
{
  String str = "Location: ";
  if (gps.location.isValid())
  {
    str = str + String(gps.location.lat(), 6);
    str = str + ", ";
    str = str + String(gps.location.lng(), 6);
  }
  else
  {
    str = str + "INVALID";
  }

  str = str + "  Date/Time: ";
  if (gps.date.isValid())
  {
    str = str + gps.date.month();
    str = str + "/";
    str = str + gps.date.day();
    str = str + "/";
    str = str + gps.date.year();
  }
  else
  {
    str = str + "INVALID";
  }

  str = str + " ";
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) str = str + "0";
    str = str + gps.time.hour();
    str = str + ":";
    if (gps.time.minute() < 10) str = str + "0";
    str = str + gps.time.minute();
    str = str + ":";
    if (gps.time.second() < 10) str = str + "0";
    str = str + gps.time.second();
    str = str + ".";
    if (gps.time.centisecond() < 10) str = str + "0";
    str = str + gps.time.centisecond();
  }
  else
  {
    str = str + "INVALID";
  }

  return str;
}
