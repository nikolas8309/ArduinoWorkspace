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
    myFile.write(readVal);
  }
}

//-------------------------------------------
void writeFileToEeprom(){
  byte valToWrite=0;
  
  for(unsigned long i=0; i<MEM_SIZE; i++)
  {
    if(!myFile.available()){
      Serial.print("EOF reached. Aborting");
      break;
    }

    valToWrite=myFile.read();
    
    i2c_eeprom.write1ByteAddress(i, valToWrite);
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
//-------------------------------------------

byte readAddress(unsigned int address)
{
  byte rData = 0xFF;
  
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  
  //Wire.write((unsigned int)(address >> 8));   // MSB
  Wire.write((unsigned int)(address & 0xFF)); // LSB
  Wire.endTransmission();  

  Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);  

  rData =  Wire.read();

  return rData;
}
