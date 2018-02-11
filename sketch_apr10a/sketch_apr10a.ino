#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); 
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND
void setup()  
{
  // set digital pin to control as an output
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
}
char a; // stores incoming character from other device
void loop() 
{
  if (BT.available())
  // if text arrived in from BT serial...
  {
    a=(BT.read());
    if (a=='1')
    {
      digitalWrite(2,LOW);//CDI
      digitalWrite(3,HIGH);//BAT1/BAT
      digitalWrite(4,HIGH);//starter
      delay (1500);
      digitalWrite(4,LOW);//starter
    }
    if (a=='2')
    {
      digitalWrite(2,HIGH);//CDI
      digitalWrite(3,LOW);//BAT/BAT1
    }
    
    // you can add more "if" statements with other characters to add more commands
  }
}
