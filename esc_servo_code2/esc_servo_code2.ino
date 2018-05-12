#include <Servo.h>
Servo esc;
int analogPin = 2;     
int throttlePin = 3;                       
int val = 0;          

void setup()
{
  Serial.begin(9600);
  esc.attach(9);
}

void loop()
{
  val = analogRead(analogPin);     // read the input pin
  //Serial.println(val);

  if (val <=80)
  {
      int throttle = analogRead(throttlePin);
      throttle = map(throttle, 0, 1023, 0, 179);
      esc.write(throttle);
      Serial.println (throttle);
      }
   else {
    Serial.println (val);
    }
    
    
    
}
