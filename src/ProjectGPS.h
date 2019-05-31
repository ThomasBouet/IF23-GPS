#ifndef DEF_PROJECTGPS
#define DEF_PROJECTGPS

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

class ProjectGPS{

public:
  ProjectGPS();
  void getLocation();

protected:
  void displayInfo();

private:
  TinyGPSPlus gps;

};

#endif
