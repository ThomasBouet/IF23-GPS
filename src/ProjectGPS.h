#ifndef DEF_PROJECTGPS
#define DEF_PROJECTGPS

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

class ProjectGPS{

public:
  ProjectGPS();
  String getLocation();

protected:
  String displayInfo();

private:
  TinyGPSPlus gps;

};

#endif
