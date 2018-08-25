#include <Wire.h>

#define READBYTES 64

uint8_t inBuffer[READBYTES];

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  delay(5000);
}

void loop()
{

  Serial.println("LOOP");
  Wire.requestFrom(0x68, READBYTES );    // request READBYTES bytes from slave device 0x68

  //while(Wire.available())    // slave may send less than requested
  for(int j=0;j<READBYTES ;j++)
  { 
    //char c = Wire.read(); // receive a byte as character
    inBuffer[j]=Wire.read();
   // Serial.print(inBuffer[j]);         // print the character
  }
  
  Serial.println();
  Serial.println("AS HEX[]");
  for(int j=0;j<READBYTES;j++){ 
    Serial.print(inBuffer[j],HEX);
    Serial.print(" ");         
  }

  Serial.println();
  Serial.println("AS CHAR[]");
  for(int j=0;j<READBYTES;j++){ 
    Serial.print((char)inBuffer[j]);
  }
  
  Serial.println();
  Serial.println("DONE");

  delay(2000);
  
}
