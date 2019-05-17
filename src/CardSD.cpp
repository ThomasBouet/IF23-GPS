#include "CardSD.h"

#define pinCS 10

Sd2Card sd;
File sdFile;
File root;

CardSD::CardSD()
{
switch(stateSD()){
  case 0:
    Serial.println("Carte mal insérée/Mauvais branchement/Mauvais pin");
    break;
  case 1:
    Serial.println("Branchement correct et carte insérée");
    break;
}
Serial.print("SD de type "); Serial.println(typeSD());
root = SD.open("/");
}

CardSD::stateSD(){
  if (!sd.init(SPI_HALF_SPEED, pinCS)) {
      //carte pas insérée, mauvais branchement, mauvais pin
      return 0;
    } else {
      //Branchement correct et carte insérée
      return 1;
    }
}

CardSD::typeSD(){
  switch (sd.type()) {
    case SD_CARD_TYPE_SD1:
      return 1;
      //break;
    case SD_CARD_TYPE_SD2:
      return 2;
      //break;
    case SD_CARD_TYPE_SDHC:
      return 3;
      //break;
    default:
      return 0;
  }
}

SDLib::File CardSD::getRoot(){
  return root;
}

CardSD::initSD(){
  if(!SD.begin(pinCS)){
    //échec de l'initialisation de la carte
    return 0;
  }
}

CardSD::createFile(String fileName){
  initSD();
  //si le fichier n'existe pas je le créé
  if(!SD.exists(fileName)){
    sdFile = SD.open(fileName, FILE_WRITE);
    sdFile.close();
  }else{
    //le fichier existe déjà
    deleteFile(fileName);
    sdFile = SD.open(fileName, FILE_WRITE);
    sdFile.close();
  }
  if(SD.exists(fileName)){
    //la création a réussi
    return 1;
  }else{
    return 0;
  }
}

CardSD::writeFile(String fileName,String content){
  initSD();
  if(!SD.exists(fileName)){
    return 0;
  }
  sdFile = SD.open(fileName, FILE_WRITE);
  if(sdFile){
    sdFile.println(content);
    sdFile.close();
    return 1;
  }else{
    //le fichier n'est pas ouvert
    return 0;
  }
}

//utilité ?
CardSD::readFile(String fileName){
  initSD();
  if(!SD.exists(fileName)){
    return 0;
  }
  sdFile = SD.open(fileName);
  if(sdFile){
    while(sdFile.available()){
      Serial.write(sdFile.read());
    }
    sdFile.close();
  }else{
    //le fichier ne s'est pas ouvert
    return 0;
  }
}

CardSD::deleteFile(String fileName){
  initSD();
  if(!SD.exists(fileName)){
    //le fichier n'existe pas
    return -1;
  }
  SD.remove(fileName);
  if(SD.exists(fileName)){
    //la suppression a échouée
    return 0;
  }
  //la suppression a fonctionnée
  return 1;
}

void CardSD::printDirectory(File dir, int numTabs) {
  initSD();
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
//
