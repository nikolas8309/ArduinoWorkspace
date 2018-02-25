 
int pinread = 2;
int data[50]; //0-49
void setup() {
    Serial.begin (9600);
      pinMode (pinread,INPUT);

    //data capturing
   for(int i=0;i<50;i++){
      data[i] = digitalRead(pinread);
      delayMicroseconds(10);
  }

    
    // i - <data>
    // i - <>
   for(int j=0;j<=100;j++){
      Serial.print (j);
      Serial.print("-");
      Serial.println (data[j]);
  }
 
}

void loop() {
}

