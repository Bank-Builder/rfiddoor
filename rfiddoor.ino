
#include <SoftwareSerial.h>
#include <EEPROM.h>

SoftwareSerial mySerial(2, 3);//pin2-Rx,pin3-Tx(note: pin3 is actually later used as volume down input)

// BLOCKSIZE = CARNOSIZE + CARDTYPE, i.e. store 1 for normal and 2 for master
#define BLOCKSIZE 11
#define CARDNOSIZE 10
#define HEADERSIZE 1
#define MAXCARDNO 10

unsigned char card[CARDNOSIZE];
unsigned char eepromcard[CARDNOSIZE];

#define MASTERTIMEOUT 5000
long lastmasterread=-MASTERTIMEOUT;
unsigned char MASTER[CARDNOSIZE+1] = "0100032D0D";

void setup()
{
  Serial.begin(9600);
  Serial.println("H4H RFID Card Reader:");
  mySerial.begin(9600);// used for receiving command data from the iPod dock.
}


void loop(){
    int r = readCard();
    if(r==1) {  
        int cardType = cardExists(); 
        if(cardType == 2)  { // is a master
          Serial.println("Master is found");
          lastmasterread = millis();
          decode(card);
        } 
        if(cardType ==1) { //norma;
           Serial.println("normal");
        } 
         
        if(cardType ==0){ // does not exist
           if(millis() - lastmasterread < MASTERTIMEOUT){
              Serial.println("Card Record");

              // this is a card record event
              writeCard(false); //write a normal card
              lastmasterread = 0;
           }
        }

     }
}


int readCard(){
    if (mySerial.available()>0){
         unsigned char i=0; 
         if(mySerial.read()==2){
             while(1){
               if(mySerial.available()) {           
                  char c=mySerial.read();
                  if(c==3) {
                    return 1;
                    break;
                  } else{
                     card[i] = c;
                     i++;
                     if(i==20) return 2; //error
                  }
               }
             }
         }
       } else{
         return 0;
       }
} 

void decode(unsigned char* data){
  unsigned char p;
  for(p=0;p<11;p++){
      char c = data[p];
      Serial.print(c);
      Serial.print("");
  }
  Serial.println();
}


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
  EEPROM.write(0,maxCardNo);
 
}


int writeCard(boolean master) {
  Serial.println("in write card");
  int r = 0;
  int nextCardNo = readMaxCardNo()+1;
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
        writeMaxCardNo(nextCardNo); 
    }
    r = true;
  } else {
    r = false;
  }
  
  
  Serial.print("exit write card result:");
  Serial.println(r);
  return r; 
}


