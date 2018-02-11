#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); 
//SoftwareSerial BT(A1,A2); 

// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND
void setup()  
{
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  // set digital pin to control as an output
  pinMode(2,OUTPUT);
  // set digital pin to control as an output
  pinMode(13, OUTPUT);
  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
  // Send test message to other device
  BT.println("Hello from Arduino");
}
char a; // stores incoming character from other device
void loop() 
{
  if (BT.available())
  // if text arrived in from BT serial...
  {
    a=(BT.read());
    Serial.print(a);
    if (a=='1')
    {
      digitalWrite(3,HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(2,HIGH);
      digitalWrite(4,HIGH);
      delay(5000);
      digitalWrite(4,LOW);
    }
    if (a=='2')
    {
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(13, LOW);
      digitalWrite(2,LOW);
    }
    if (a=='?')
    {
      BT.println("Send '1' to turn LED on");
      BT.println("Send '2' to turn LED on");
    }   
    // you can add more "if" statements with other characters to add more commands
  }
}
