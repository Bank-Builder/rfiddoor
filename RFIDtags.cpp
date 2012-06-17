/*
  RFIDtags.cpp - Library for accessing blocks of data
 in the in built Arduino EEPROM.
 Created by Bank-Builder, May 26, 2012
 Released into the public domain.
 */
#include <EEPROM.h>

#include "Arduino.h"
#include "RFIDtags.h"
#include <SoftwareSerial.h>



//<<constructor>> setup the RFIDtags class with the data blocksize
RFIDtags::RFIDtags (int taglength) {
  //initialise class variables    
  _taglength = taglength +1;  //add 1 char for the tag_type indicator
  _reset = '^'; //default reset character
  _maxtags = 255 / (_taglength); //EEPROM only has 255 bytes available for storing tags

  // read the EEPROM into the _eeprom array;
  for (int i = 0; i < 512; i++) {
    _eeprom[i] = EEPROM.read(i);
  }
}

// Clear resets the _eeprom array and hard=true resets the EEPROM. Beware not to put this 
// in your main loop() as it will quickly kill your EEPROM 
void RFIDtags::clear(boolean hard) {
  // write a _reset character to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++) {
    //flash the LED while busy
    //digitalWrite(13, HIGH);
    _eeprom[i] = _reset;
    if (hard) {
      EEPROM.write(i, _reset);
    }
    delay(100);
    //digitalWrite(13, LOW);
  }
}

int RFIDtags::gettagcount(){
  return _tagcount;
}

void RFIDtags::settagcount(int tagcount){
  _tagcount = tagcount;
}

//Finds a tag by id and returns the tag type ie NONE, NORMAL or MASTER 
int RFIDtags::findtag(char* p) {
  int r = TAG_NONE;
  int foundmatch = 0;
  for (int j=0; j < _maxtags; j++){

    if (foundmatch = _taglength) { 
      //read the last character of the last tag to get the tag type and exit
      r = _eeprom[(j*_taglength) -1];
      break;
    }

    for(int i=0; i< _taglength; i++){
      if( _eeprom[(j*_taglength) + i] == *p) { //match consecutive chars in tag serial number
        foundmatch++;
      } 
      else {
        foundmatch = 0;
      }
      p++;
    }
  }
  return r;
}


//Adds a tag to the tag store and returns false if tag store is full
int RFIDtags::addtag(char* tag, int tagtype) {
  boolean r = false;
  int startpos = _tagcount * _taglength;
  if (( _tagcount < _maxtags) && (findtag(tag) == TAG_NONE )){
      // Write tag to tag store
      for(int i=0; i < _taglength; i++){
        EEPROM.write( startpos + i,tag[i]);  //write to EEPROM
        _eeprom[startpos + i] = tag[i];      //write to RAM array
      }
      // Write card type, if first tag then make it a MASTER tag
      if (_tagcount == 0) {
        tagtype = TAG_MASTER;
      }
      EEPROM.write(startpos + _taglength, char(tagtype)); //write to EEPROM
      _eeprom[startpos + _taglength] = tagtype;      //write to RAM array
      //Update the tag count
      _tagcount = _tagcount + 1;
      r = true;
  } 
  else { //it means there is no more space to add tags
    r = false;
  }
  return r; 
}



//--------------------------------------------------

/**
 * int pin = 13;
 * volatile int state = LOW;
 * 
 * #define MASTERTIMEOUT 5000
 * long lastmasterread=-MASTERTIMEOUT;
 * unsigned char MASTER[CARDNOSIZE+1] = "0100032D0D";
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * // 0 = fail
 * // 1 = normal
 * // 2 = master
 * int readCard(int cardno) {
 * Serial.print("in read card cardno:");
 * Serial.println(cardno);
 * 
 * int r=0;
 * if(cardno> readMaxCardNo() || cardno<0) {
 * r = 0;
 * }else{
 * for(int i=0; i<CARDNOSIZE; i++){
 * eepromcard[i] = EEPROM.read(HEADERSIZE + cardno*BLOCKSIZE + i);
 * }
 * // Calculate checksum
 * 
 * // Determine cardtype
 * r = EEPROM.read(HEADERSIZE + cardno*BLOCKSIZE + CARDNOSIZE );  // offset for checksum
 * if(r!=1 && r!=2) r=0;
 * }
 * Serial.print("exit read card result:");
 * Serial.println(r);
 * 
 * return r;
 * }
 * 
 * 
 * 
 * // **** End of EEPROM Code ***
 * 
 * 
 * 
 * 
 * 
 */




