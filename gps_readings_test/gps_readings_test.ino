
#include "utilities.h"

void setup() {
    Serial.begin(115200);
counter=0;

  //for receiver read 
   pinMode(RC_CH4_INPUT, INPUT);
   attachInterrupt(digitalPinToInterrupt(RC_CH4_INPUT), calc_input, CHANGE);
}

void loop() {
  Serial.print("COUNTER=");
Serial.println(counter);

  if (!hasSignal()) {
    Serial.println ("xathike to sima");
  }
    else {Serial.println ("vrethike to sima");
    }
    delay(1000);
}
