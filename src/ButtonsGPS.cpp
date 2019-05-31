//#include <Arduino.h>
#include "ButtonsGPS.h"

#define BP1 15
#define BP0 16
#define BPEN 17

  ButtonsGPS::ButtonsGPS()
  {
    debouncer = Bounce();
    debouncerBP0 = Bounce();
    debouncerBP1 = Bounce();

    pinMode(BPEN, INPUT_PULLUP);
    debouncer.attach(BPEN);
    debouncer.interval(5);

    pinMode(BP0, INPUT_PULLUP);
    debouncerBP0.attach(BP0);
    debouncerBP0.interval(5);

    pinMode(BP1, INPUT_PULLUP);
    debouncerBP1.attach(BP1);
    debouncerBP1.interval(5);
  }

  int ButtonsGPS::readButtons(){
    int state;
    debouncer.update();
    debouncerBP0.update();
    debouncerBP1.update();
    if (debouncer.rose() == HIGH) {
      if(debouncerBP1.fell() == true && debouncerBP0.fell() == true){
        state = 1;
      }
      else if(debouncerBP1.fell() == true && debouncerBP0.fell() == false){
        state = 2;
      }
      else if(debouncerBP1.fell() == false && debouncerBP0.fell() == true){
        state = 3;
      }
      else if(debouncerBP1.fell() == false && debouncerBP0.fell() == false){
        state = 4;
      }
    }else{
      state = 0;
    }
    return state;
  }
