#include <Wire.h>
#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"

/* Assign a unique ID to this sensor at the same time */
//Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
LSM303C myIMU;
 
void setup(void) 
{
  Serial.begin(9600);
  
  Serial.println("Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if (myIMU.begin() != IMU_SUCCESS)
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}
 
void loop(void) 
{
  float x_axis = (myIMU.readMagX()/10);
  float y_axis = (myIMU.readMagY()/10);
  Serial.println (y_axis);
  Serial.println (myIMU.readMagY());
  /* Get a new sensor event */ 
  //sensors_event_t event; 
  //mag.getEvent(&event);
  
  float Pi = 3.14159;
  
  // Calculate the angle of the vector y,x
  float heading = (atan2( y_axis, x_axis) * 180) / Pi;
  
  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  Serial.print("Compass Heading: ");
  Serial.println(heading);
  delay(500);
}
