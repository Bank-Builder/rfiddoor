/*
  EEPROM_RFID.cpp - Library for accessing blocks of data
  in the inbuilt Arduino EEPROM.
  Created by Bank-Builder, May 26, 2012
  Released into the public domain.
*/

#include "Arduino.h"
#include "EEPROM_RFID.h"
#include <EEPROM.h>

//<<constructor>> setup the EEPROM_RFID class wth the data blocksize
EEPROM_RFID::EEPROM_RFID (int blocksize) {
    //initialise class variables    
    _blocksize = blocksize;
    _reset = '^';//default reset character  
  
    // read the EEPROM into the _eeprom array;
    //...do it here ...
}

void EEPROM_RFID::clear() {
  // write a 0 to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++) {
    //flash the LED while busy
    digitalWrite(13, HIGH);
    _eeprom[i] = _reset;
    delay(100);
    digitalWrite(13, LOW);
  }
  
}


//--------------------------------------------------

/*** Begin EEPROM Code ***
This EEPROM code reads and write blocks of EEPROM_BLOCKSIZE from/to the Arduino's built in EEPROM.  
It is designed to minimise the number of reads/writes to extend the EEPROM life as long as possible
Upon Setup, create an array of the EEPROM data for reading
The code uses EEPROM_DELIMITER to delimit the last bloack of data. This defaulted to "^".



/***
// BLOCKSIZE = CARNOSIZE + CARDTYPE, i.e. store 1 for normal and 2 for master
#define BLOCKSIZE 11
#define CARDNOSIZE 10
#define HEADERSIZE 1
#define MAXCARDNO 10

unsigned char card[CARDNOSIZE];
unsigned char eepromcard[CARDNOSIZE];

int pin = 13;
volatile int state = LOW;

#define MASTERTIMEOUT 5000
long lastmasterread=-MASTERTIMEOUT;
unsigned char MASTER[CARDNOSIZE+1] = "0100032D0D";



// 0 = does not exist
// 1 = does exist and normal
// 2 = master
int cardExists(){
  Serial.println("in card exists");
  int r=0;
  if(compare(MASTER)==1) {
    r=2; 
  } else {
    for(int i=0; i< readMaxCardNo(); i++){
       int cardReadResult = readCard(i);
       Serial.print("Card read from eeprom:");
       decode(eepromcard);
       if(compare(eepromcard)==1){
           r = cardReadResult;
           break;
       }
    }
  }
  Serial.print("card exists returns:");
  Serial.println(r);

  return r;
  
}


int compare(unsigned char* p){
   int r = 1;
   for(int i=0; i< CARDNOSIZE; i++){
      if(card[i] == *p) p++;
      else {
        r = 0;
        break;
      }
   }
   return r;
}


// 0 = fail
// 1 = normal
// 2 = master
int readCard(int cardno) {
  Serial.print("in read card cardno:");
  Serial.println(cardno);

  int r=0;
  if(cardno> readMaxCardNo() || cardno<0) {
    r = 0;
  }else{
    for(int i=0; i<CARDNOSIZE; i++){
       eepromcard[i] = EEPROM.read(HEADERSIZE + cardno*BLOCKSIZE + i);
    }
    // Calculate checksum
    
    // Determine cardtype
    r = EEPROM.read(HEADERSIZE + cardno*BLOCKSIZE + CARDNOSIZE );  // offset for checksum
    if(r!=1 && r!=2) r=0;
  }
  Serial.print("exit read card result:");
  Serial.println(r);

  return r;
}

int readMaxCardNo(){
  int r = EEPROM.read(0);
  Serial.print("ReadMax Cardno:");
  Serial.println(r);
  return r;
}

void writeMaxCardNo(int maxCardNo){
  //EEPROM.write(0,maxCardNo);
 
}

// **** End of EEPROM Code ***



int writeCard(boolean master) {
  Serial.println("in write card");
  int r = 0;
  int nextCardNo = readMaxCardNo();
  if(nextCardNo < MAXCARDNO) {
    if(cardExists()==0){
        // Write card no
        for(int i=0; i<CARDNOSIZE; i++){
          EEPROM.write(HEADERSIZE + nextCardNo*BLOCKSIZE + i,card[i]);
        }
        // Write card type
        int cardtype = 1;
        if(master) cardtype =2;
        EEPROM.write(HEADERSIZE + nextCardNo*BLOCKSIZE + CARDNOSIZE,cardtype);
        //Update the header
        writeMaxCardNo(nextCardNo+1); 
    }
    r = true;
  } else {
    r = false;
  }
  
  
  Serial.print("exit write card result:");
  Serial.println(r);
  return r; 
}


*/
