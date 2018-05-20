#include <Wire.h>
#include <MechaQMC5883.h>

MechaQMC5883 qmc;

union { 
  int16_t i; 
  uint16_t u;
} Converter;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  qmc.init();
  //qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_2G,OSR_256);
}

void loop() {
  uint16_t x, y, z;
  float azimuth;
  //float azimuth; //is supporting float too
  qmc.read(&x,&y,&z);
  //azimuth = qmc.azimuth(&y,&x);//you can get custom azimuth
  //Converter;
  Converter.u=x;
  int16_t xInt=Converter.i;

  Converter.u=y;
  int16_t yInt=Converter.i;

  Converter.u=z;
  int16_t zInt=Converter.i;

  azimuth=azi((float)yInt,(float)xInt);
  
  Serial.print("x: ");
  Serial.print(xInt);
  Serial.print(" y: ");
  Serial.print(yInt);
  Serial.print(" z: ");
  Serial.print(zInt);
  Serial.print(" a: ");
  Serial.print(azimuth);
  Serial.println();
  delay(200);
}


float azi(float a, float b){
  float azimuth = atan2(a,b) * 180.0/PI;
  return azimuth < 0?360 + azimuth:azimuth;
}
