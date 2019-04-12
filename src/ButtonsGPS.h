#ifndef DEF_BUTTONSGPS
#define DEF_BUTTONSGPS

#include <Bounce2.h>

class ButtonsGPS{

public:
  ButtonsGPS();
  int readButtons();


private:
  Bounce debouncer;


};

#endif
