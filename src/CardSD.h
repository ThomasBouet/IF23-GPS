#ifndef DEF_CARDSD
#define DEF_CARDSD

#include <SPI.h>
#include <SD.h>

class CardSD{

public:
  CardSD();
  SDLib::File getRoot();
  void printDirectory(SDLib::File, int);
  int existingFile(String);
  int createFile(String);
  int writeFile(String, String);
  int readFile(String);
  int deleteFile(String);


protected:
  int stateSD();
  int typeSD();
  int initSD();
};
#endif
