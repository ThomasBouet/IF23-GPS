//#include <Arduino.h>
#include "ButtonsGPS.h"

//Boutons
#define pinBtn1 15
#define pinBtn0 16
#define pinBtnEn 17


  ButtonsGPS::ButtonsGPS()
  {
    debouncer = Bounce();

    pinMode(pinBtn0, INPUT);
    pinMode(pinBtn1, INPUT);
    pinMode(pinBtnEn, INPUT);
    debouncer.attach(pinBtnEn);
    debouncer.interval(5); // interval in ms
  }


  ButtonsGPS::readButtons(){
    int state = 0;

    while(state == 0){
      debouncer.update();
      if (debouncer.read()) {
        switch (digitalRead(pinBtn1) * 2 + digitalRead(pinBtn0)) {
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

        }
      }






      // while(state == 0){
      //   debouncer.update();
      //   if (debouncer.read()) {
      //     switch (digitalRead(pinBtn1) * 2 + digitalRead(pinBtn0)) {
      //       case 0:
      //         return 1;
      //         //break;
      //
      //       case 1:
      //         return 2;
      //       //  break;
      //
      //       case 2:
      //         return 3;
      //       //  break;
      //
      //       case 3:
      //         return 4;
      //       //  break;
      //
      //     }
      //   }
      // else{
      //   //lcd.setCursor(0, 0);
      //   return 0;
      // }

    }

    return state;
  }




//}
