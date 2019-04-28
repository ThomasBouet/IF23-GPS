//#include <Arduino.h>
#include "ButtonsGPS.h"

//Boutons
#define pinBtn1 15
#define pinBtn0 16
#define pinBtnEn 17


  ButtonsGPS::ButtonsGPS()
  {
    debouncer = Bounce();
    debouncerBP0 = Bounce();
    debouncerBP1 = Bounce();

    pinMode(pinBtn0, INPUT_PULLUP);
    pinMode(pinBtn1, INPUT_PULLUP);
    pinMode(pinBtnEn, INPUT_PULLUP);
    debouncer.attach(pinBtnEn);
    debouncer.interval(10); // interval in ms

    debouncerBP0.attach(pinBtn0);
    debouncerBP0.interval(10);

    debouncerBP1.attach(pinBtn1);
    debouncerBP1.interval(10);
  }

  ButtonsGPS::readButtons(){
    int state = 0;

    while(state == 0){
      debouncer.update();
      if (debouncer.rose()) {
        debouncerBP0.update();
        debouncerBP1.update();
        switch (debouncerBP1.read() * 2 + debouncerBP0.read()) {
          case 0:
            state = 1;
            break;

          case 1:
            state = 2;
            break;

          case 2:
            state = 3;
            break;

          case 3:
            state = 4;
            break;

          default:
            state = 0;
            break;
        }

      }/*else{
        return 0;
      }*/


    }

    return state;
  }
