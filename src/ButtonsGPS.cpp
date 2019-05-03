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

    pinMode(pinBtn0, INPUT);
    pinMode(pinBtn1, INPUT);
    pinMode(pinBtnEn, INPUT);
    debouncer.attach(pinBtnEn);
    debouncer.interval(5); // interval in ms

    debouncerBP0.attach(pinBtn0);
    debouncerBP0.interval(5);

    debouncerBP1.attach(pinBtn1);
    debouncerBP1.interval(5);
  }

  ButtonsGPS::readButtons(){
    int state = 0;
    while(state == 0){
      debouncer.update();
      if (debouncer.rose()) {
        debouncerBP0.update();
        debouncerBP1.update();
        if(debouncerBP1.read() == LOW && debouncerBP0.read() == LOW){
          state = 1;
        }
        else if(debouncerBP1.read() == LOW && debouncerBP0.read() == HIGH){
          state = 2;
        }
        else if(debouncerBP1.read() == HIGH && debouncerBP0.read() == LOW){
          state = 3;
        }
        else if(debouncerBP1.read() == HIGH && debouncerBP0.read() == HIGH){
          state = 4;
        }
        /*switch (debouncerBP1.read() * 2 + debouncerBP0.read()) {
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
        }*/
        Serial.print("State : ");Serial.println(state);
        Serial.print("BP1 ");Serial.print(debouncerBP1.read());Serial.print(" BP0 ");Serial.println(debouncerBP0.read());

      }/*else{
        return 0;
      }*/


    }

    return state;
  }
