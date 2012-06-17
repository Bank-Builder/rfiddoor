/*
  RFIDtags.h - Library for managing RFID Tags utilising EEPROM.
  Created by Bank-Builder, May 26, 2012
  Released into the public domain.
*/

#ifndef RFIDtags_h
#define RFIDtags_h

#include "Arduino.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>

//tag types
#define TAG_NONE 0
#define TAG_NORMAL 1
#define TAG_MASTER 2
        
class RFIDtags
{
    public:
        RFIDtags(int taglength);         //constructor
        void clear(boolean hard);                    //clears the EEPROM data & associated array
        int addtag(char* tag, int tagtype);    //adds a tag of taglength to the tags store, TRUE if succesful
        int findtag(char* p);           //finds a tag in the tag store, returns tag type
        int gettagcount();              //gets the number of tags in tag store
        void settagcount(int tagCount); //sets the number of tags in the tag store
        char* readtag();                //reads a tag from the RFID sensor

    private:
        int _taglength;
        int _maxtags;
        char _reset;
        char _eeprom[255];
        int _tagcount;
};

#endif
