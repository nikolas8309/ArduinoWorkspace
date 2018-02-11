#ifndef __EEPROMCLONEUTILITY
#define __EEPROMCLONEUTILITY


#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// from https://github.com/QuentinCG/Arduino-I2C-EEPROM-library
#include <I2CEEPROM.h>

#define EEPROM_I2C_ADDRESS 0x55
#define MAX_BYTE_VAL 255
#define MAX_BYTE_BLOCK 128
#define KB_VAL 1024

const unsigned long MEM_SIZE = 8192;
I2CEEPROM i2c_eeprom(EEPROM_I2C_ADDRESS ); // Create I2C EEPROM instance

File myFile;


#endif

