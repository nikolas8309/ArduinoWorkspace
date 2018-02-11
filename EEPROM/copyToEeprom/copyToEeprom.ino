#include "Wire.h"
#include <SPI.h>
#include <SD.h>

//got it from https://github.com/QuentinCG/Arduino-I2C-EEPROM-library
#include <I2CEEPROM.h>

#define EEPROM_I2C_ADDRESS 0x55
#define MAX_BYTE_VAL 255
#define MAX_BYTE_BLOCK 128
#define KB_VAL 1024

const unsigned long MEM_SIZE = 8192;

File myFile;
I2CEEPROM i2c_eeprom(EEPROM_I2C_ADDRESS ); // Create I2C EEPROM instance


void setup() 
{
  Wire.begin();
  Serial.begin(9600);

  // 
  if(initSd())
  {
    
    //readFromEeprom();
    writeFileToEeprom();
    myFile.close();
  }
  delay(500);
  
  Serial.println(F("Done"));
  
  pinMode(13, OUTPUT);
  pinMode(13,HIGH);
}

void loop() 
{

}

void writeFileToEeprom(){
  byte valToWrite=0;
  
  for(unsigned long i=0; i<MEM_SIZE; i++)
  {
    if(!myFile.available()){
      Serial.print("EOF reached. Aborting");
      break;
    }

    valToWrite=myFile.read();
    
    i2c_eeprom.write(i, valToWrite);
      //Serial.print("Write: 0x");
      //Serial.print(i, HEX);
      //Serial.print(" (address) -> 0x");
      //Serial.print(valToWrite, HEX);
      //Serial.print(" (data)\n");
    
    
    
    // For debugging/info only
    if((i % KB_VAL == 0) && (i > 1))
    {
      unsigned long total = (unsigned long) (i / KB_VAL);
      Serial.print(F("Wrote "));
      Serial.print(total);
      Serial.println(F(" Kb"));
    }

    
    
  }
  
}

void readFromEeprom()
{
  byte readVal = 0;
  
  for(unsigned long i=0; i<MEM_SIZE; i++)
  {
    // Read from EEPROM at the current address
    readVal = readAddress(i);

    // For debugging/info only
    if((i % KB_VAL == 0) && (i > 1))
    {
      unsigned long total = (unsigned long) (i / KB_VAL);
      Serial.print(F("Wrote "));
      Serial.print(total);
      Serial.println(F(" Kb"));
    }

    // Write the value to the SDE Card
    myFile.println(readVal, DEC);
  }
}

byte readAddress(unsigned int address)
{
  byte rData = 0xFF;
  
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  
  Wire.write((unsigned int)(address >> 8));   // MSB
  Wire.write((unsigned int)(address & 0xFF)); // LSB
  Wire.endTransmission();  

  Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);  

  rData =  Wire.read();

  return rData;
}

bool initSd()
{
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  //pinMode(10, OUTPUT);
  //pinMode(9, OUTPUT);

  if (!SD.begin(4)) 
  {
    Serial.println(F("initialization failed!"));
    return false;
  }
  Serial.println(F("initialization done."));

  myFile = SD.open("image.txt");

  if(myFile)
  {
    Serial.println(F("successfully opened image.txt"));
    return true;
  }
  else
  {
    Serial.println(F("error opening dump.txt"));
    return false;
  } 
}


