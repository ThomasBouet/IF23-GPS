#ifndef DEF_BUTTONSGPS
#define DEF_BUTTONSGPS

#include <Bounce2.h>

class ButtonsGPS{

public:
  ButtonsGPS();
  int readButtons();


private:
  Bounce debouncer;
  Bounce debouncerBP0;
  Bounce debouncerBP1;


};

#endif
