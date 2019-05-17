#include "ProjectGPS.h"

#define GPS_TX 2
#define GPS_RX 3

SoftwareSerial ss(GPS_RX, GPS_TX);

ProjectGPS::ProjectGPS(){
  ss.begin(4800);
}

String ProjectGPS::getLocation()
{
  bool newData = false;
  unsigned long chars;

  while (ss.available()){
    char c = ss.read();
    //Serial.write(c);
    if (gps.encode(c)){
      newData = true;
    }
  }

  return displayInfo();
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
