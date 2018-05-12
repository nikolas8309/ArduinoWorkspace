#include "EnableInterrupt.h"


#define SERIAL_PORT_SPEED 9600
#define RC_NUM_CHANNELS  4

#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3

#define RC_CH1_INPUT  A0
#define RC_CH2_INPUT  A1
#define RC_CH3_INPUT  A2
#define RC_CH4_INPUT  A3

uint16_t rc_values;
uint32_t rc_start;
volatile uint16_t rc_shared;
int ledpin = 13;
int minLimit = 900;
int maxLimit = 1450;

void rc_read_values() {
  noInterrupts();
  //memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  rc_values=rc_shared;
  interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    rc_start = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start);
    rc_shared = rc_compare;
  }
}

void calc_ch4() { calc_input(RC_CH4, RC_CH4_INPUT); }

 
void setup() {
  Serial.begin(SERIAL_PORT_SPEED);

  pinMode(RC_CH4_INPUT, INPUT);
  enableInterrupt(RC_CH4_INPUT, calc_ch4, CHANGE);
  pinMode(ledpin,OUTPUT );
}
void loop() {
  

  //Serial.print("CH1:"); Serial.print(rc_values[RC_CH1]); Serial.print("\t");
  //Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]); Serial.print("\t");
  //Serial.print("CH3:"); Serial.print(rc_values[RC_CH3]); Serial.print("\t");
  Serial.print("\nCH4:"); Serial.println(rc_values);

  bool isInLimit=true;
  for(int i=0;i<10;i++){
      delay(100);
      rc_read_values();
       Serial.println (rc_values);
      if(rc_values != constrain(rc_values, minLimit,maxLimit )){
        isInLimit=false;
        break;
      }
  }
  if(isInLimit){
     digitalWrite(ledpin, HIGH);
  }else{
      digitalWrite(ledpin,LOW);
  }
  delay (500);
   
}
