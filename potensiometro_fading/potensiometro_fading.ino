int sensorPin = A2;    // select the input pin for the potentiometer
int ledPin = 9;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
 sensorValue = analogRead(sensorPin);
 Serial.print(sensorValue);
 Serial.print ("  ");
 delay(500);
 sensorValue=map(sensorValue,0,1023,0,255);
 Serial.println (sensorValue);
 analogWrite (ledPin,sensorValue);


 //Serial.println (sensorValue);
}
 

