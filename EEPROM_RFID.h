/*
  EEPROM_RFID.h - Library for accessing blocks of EEPROM data.
  Created by Bank-Builder, May 26, 2012
  Released into the public domain.
*/

#ifndef EEPROM_RFID_h
#define EEPROM_RFID_h

#include "Arduino.h"

class EEPROM_RFID
{
    public:
        EEPROM_RFID(int blocksize); //constructor
    //    void setblocksize(int blocksize);
    //    int getblocksize();
    //    int findblock();  //returns blocknumber if datablock is found else 0
    //    int readblock(int blocknumber); //returns the datablock at position blocknumber
    //    int writeblock(); // writes a datablock
        void clear(); //clears the EEPROM data & associated array
    private:
        int _blocksize;
        char _reset;
        char _eeprom[255];
};

#endif
