#ifndef DEF_CARDSD
#define DEF_CARDSD

#include <SPI.h>
#include <SD.h>

class CardSD{

public:
  CardSD();

protected:
  int stateSD();
  int typeSD();
  int initSD();
  int createFile(String);
  int writeFile(String, String);
  int readFile(String);
  int deleteFile(String);


};
#endif
