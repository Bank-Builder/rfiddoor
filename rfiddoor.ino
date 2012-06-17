#include "RFIDtags.h"
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define TAGLENGTH 10
#define HARD true
#define SOFT false
#define MASTERTIMEOUT 5000 //5 seconds
long lastmasterread=-MASTERTIMEOUT;
unsigned char MASTER[TAGLENGTH+1] = "0100032D0D";

//Use the RFIDtags library to store & lookup registered RFID Tags
//RFIDtags tagstore(TAGLENGTH); //10 digits for tag code
SoftwareSerial mySerial(2, 3);//pin2-Rx,pin3-Tx





void setup() {
  Serial.begin(115200);
  Serial.println("Bank-Builder RFID Door Controller:");
  mySerial.begin(9600);// used for receiving command data from the iPod dock.
  Serial.println("Setting up reset interrupt");
  
  

  //attachInterrupt(0, hardreset, CHANGE);
  //tagstore.clear(SOFT);
}

void hardreset() {
 // tagstore.clear(HARD);
}


void opendoor() {
}


void loop(){
  char c;
  int i = 0;
  char tag[TAGLENGTH+1];
  
   while (mySerial.available()>0){
    c = mySerial.read();
    if ( (int(c) != 3) && (int(c) != 20) ){
      Serial.print(c); //Serial.print(int(c));
      i++;
      tag[i] = c;
    } else {
      Serial.print("\n");
      Serial.print(int(c));
      Serial.print("\n");
      i = 0;
    }
    
   }
  //Serial.println("loop");
     
  
  //2. read serial interface 
  
   /**
    while (mySerial.available()>0){
    c = mySerial.read();
    Serial.print(c);
    
  while (mySerial.available()>0){
    c = mySerial.read()
    serial.print(c);
  }   
    if (c != '\n') {
          tag[i] = c;
          i++;
          if(i > _taglength) {
               //error
          }
          if (i == _taglength) {
              return TAG_NORMAL;
          }  
    }      
  }     
  
  **/
  
  //3. if valid tag is found then unlock the door
  
  //4. if a MASTER is found then set enrolemnt period 
  
  //5. if a new tag is found and enrolemnt period true then addtag
  
 
}


