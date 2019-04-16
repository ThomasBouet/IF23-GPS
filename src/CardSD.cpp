#include "CardSD.h"

#define pinCS 10

Sd2Card sd;
File sdFile;

CardSD::CardSD()
{
//do not know what to put here
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

CardSD::createFile(String fileName){
  if(!SD.begin(pinCS)){
    //échec de l'initialisation de la carte
    return 0;
  }
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

CardSD::readFile(String fileName){
  if(!SD.exists(fileName)){
    return 0;
  }
  sdFile = SD.open(fileName);
  if(sdFile){
    while(sdFile.available()){
      //read the content
    }
    sdFile.close();
  }else{
    //le fichier ne s'est pas ouvert
    return 0;
  }
}

CardSD::deleteFile(String fileName){
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
