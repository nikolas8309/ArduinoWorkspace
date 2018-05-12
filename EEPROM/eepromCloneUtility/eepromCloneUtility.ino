#include "eepromCloneUtility.h"

const int eeprom2SdButton=7;
const int sd2EepromButton=6;

boolean eeprom2SdButtonPreviousState;
boolean sd2EepromButtonPreviousState;

void setup() {

    pinMode(eeprom2SdButton,INPUT);
    digitalWrite(eeprom2SdButton,HIGH);

    pinMode(sd2EepromButton,INPUT);
    digitalWrite(sd2EepromButton,HIGH);

    eeprom2SdButtonPreviousState=digitalRead(eeprom2SdButton);
    sd2EepromButtonPreviousState=digitalRead(sd2EepromButton);

    Wire.begin();

    Serial.begin(9600);
    Serial.println("Beginning");

    scanI2CBus();

}

void loop() {

    boolean eeprom2SdButtonState=digitalRead(eeprom2SdButton);
    boolean sd2EepromButtonState=digitalRead(sd2EepromButton);

    if(eeprom2SdButtonState != eeprom2SdButtonPreviousState && eeprom2SdButtonState ==LOW){
        eeprom2Sd(); 
    }

    if(sd2EepromButtonState != sd2EepromButtonPreviousState && sd2EepromButtonState ==LOW){
        sd2Eeprom(); 
    }


    eeprom2SdButtonPreviousState=eeprom2SdButtonState;
    sd2EepromButtonPreviousState=sd2EepromButtonState;
    delay(50);
}


void eeprom2Sd(){
    Serial.println("eeprom2SD running");
    if(initSd() && openFileForWrite()){
        // Read from EEPROM and write to SD card
        readFromEeprom();
        closeFile();
    }
    delay(500);

    Serial.println(F("Done"));
}

void sd2Eeprom(){
    Serial.println("sd2Eeprom running");
    
    if(initSd() && openFileForRead()){
        // Read from EEPROM and write to SD card
        writeFileToEeprom();
        closeFile();
    }
    delay(500);

    Serial.println(F("Done"));
}





