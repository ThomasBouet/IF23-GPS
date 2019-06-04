#include <initialisation.h>
#include <ButtonsGPS.h>

//setup
void initProject(){
  Serial.begin(9600);
  ss.begin(4800);
  lcd.begin(8, 2);
  pinMode(VBAT, INPUT);
  currentState = BATTERY;
  Serial.println("Initialisation");
  fileIndex = 1;
  isWriting = false;
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

static String printInt(unsigned long val, bool valid, int len)
{
  String str = "";
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0)
    sz[len-1] = ' ';
  str += String(sz);
  return str;
}

static String printFloat(float val, bool valid, int len, int prec)
{
  String str = "";
  if (!valid)
  {
    while (len-- > 1)
      str += '*';
    str += ' ';
  }
  else
  {
    str += String(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      str += ' ';
  }
  return str;
}

static String printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  String str = "";
  if (!d.isValid())
  {
    str += "********** ";
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    str += String(sz);
  }

  if (!t.isValid())
  {
    str += "******** ";
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    str += String(sz);
  }

  str += printInt(d.age(), d.isValid(), 5);
  return str;
}

static String printStr(const char *str, int len)
{
  String stri = "";
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    stri += String(i<slen ? str[i] : ' ');
  return stri;
}

String displayInfo()
{
  String str = "";
  str += printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
  str += printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);
  str += printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  str += printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  str += printInt(gps.location.age(), gps.location.isValid(), 5);
  str += printDateTime(gps.date, gps.time);
  str += printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  str += printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
  str += printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
  str += printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);
  str += printInt(gps.charsProcessed(), true, 6);
  str += printInt(gps.sentencesWithFix(), true, 10);
  str += printInt(gps.failedChecksum(), true, 9);
  return str;
}

void gpsLocation(int t){
  lcd.setCursor(0, 1);
  lcd.print("Wait sig");
  String file = String(fileIndex)+".txt";
  if(!isWriting){
    while(sdCard.existingFile(file) == 1){
      fileIndex ++;
      file = String(fileIndex)+".txt";
    }
    if(sdCard.createFile(file) == 1){
      isWriting = true;
      sdCard.writeFile(file, file);
      sdCard.writeFile(file, String("Sats HDOP  Latitude   Longitude   Fix  Date       Time     Date Alt    Course Speed Card   Chars Sentences Checksum"));
      sdCard.writeFile(file, String("           (deg)      (deg)       Age                      Age  (m)    --- from GPS ----   RX    RX        Fail"));
      sdCard.writeFile(file, String("------------------------------------------------------------------------------------------------------------------"));
    }
  }else{
    while (ss.available() > 0){
      if (gps.encode(ss.read())){
        lcd.print("sig fond");
        if(gps.location.isValid()){
          String content = displayInfo();
          Serial.println(content);
          sdCard.writeFile(file, content);
        }
      }
      if(btn.readButtons() == 4){
        isWriting = false;
        lcd.clear();
        lcd.print("Fin");
        isDoingSmth = 0;
      }
    }
      if (millis() > t+6000 && gps.charsProcessed() < 10)
      {
        Serial.println(F("No GPS detected: check wiring"));
        isWriting = false;
        lcd.clear();
        lcd.print("Fin");
        isDoingSmth = 0;
      }
    }

}
