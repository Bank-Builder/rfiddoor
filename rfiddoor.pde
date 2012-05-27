#include "EEPROM_RFID.h"
#include <SoftwareSerial.h>


//Use the EEPROM to store & lookup registered RFID Tags
EEPROM_RFID tags(11);

//Use pin2-Rx,pin3-Tx
SoftwareSerial mySerial(2, 3);

void setup() {
  Serial.begin(9600);
  Serial.println("Bank-Builder RFID Door Controller:");
  mySerial.begin(9600);// used for receiving command data from the iPod dock.
  //Serial.println("Setting up reset interrupt");
  //pinMode(pin, OUTPUT);
  //attachInterrupt(0, resetEEPROM, CHANGE);
  tags.clear();
}


void loop(){
   //just pleazse compile!
}

