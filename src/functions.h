#include <initialisation.h>
#include <ButtonsGPS.h>

//setup
void initProject(){
  Serial.begin(9600);
  lcd.begin(8, 2);
  pinMode(VBAT, INPUT);
  currentState = BATTERY;
  Serial.println("Initialisation");
}

void battery(){
  lcd.setCursor(4, 1);
  tension = (float)(analogRead(VBAT))/1023.0*6.5;
  lcd.print(tension);
  lcd.setCursor(3, 1);
  lcd.print("V");
  if(btn.readButtons() == 4){
    lcd.clear();
    isDoingSmth = 0;
  }
}

void gpsLocation(){
  Serial.println("gonna get some coordinates ;)");
  pgps.getLocation();
  //Serial.println(String(pgps.getLocation()));
  if(btn.readButtons() == 4){
    lcd.clear();
    isDoingSmth = 0;
  }
}
