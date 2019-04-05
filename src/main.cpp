#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SD.h>

const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9, pinBat = 14, btnBit0 = 16, btnBit1 = 15, btnEnable = 17;
float tension;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.begin(8, 2);
  pinMode(pinBat, INPUT);
  pinMode(btnBit0, INPUT);
  pinMode(btnBit1, INPUT);
  pinMode(btnEnable, INPUT);
  lcd.noDisplay();
  lcd.display();


}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  tension = (float(analogRead(pinBat))/1023.0)*6.5;
  lcd.print(tension);
  if (digitalRead(btnEnable) == HIGH) {
    lcd.setCursor(1,0);
    int btn = (digitalRead(btnBit1))*10 + digitalRead(btnBit0);
    Serial.print(btn);
    switch (btn) {
      case int(0): lcd.clear(); lcd.print("1"); break;
      case int(1): lcd.clear(); lcd.print("2"); break;
      case int(10): lcd.clear(); lcd.print("3"); break;
      case int(11): lcd.clear(); lcd.print("4"); break;
    }
  }


}
