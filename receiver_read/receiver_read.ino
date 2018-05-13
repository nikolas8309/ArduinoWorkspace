#include "EnableInterrupt.h"


#define SERIAL_PORT_SPEED 9600

#define RC_CH4_INPUT  A3

uint16_t rc_values;
uint32_t rc_start;
volatile uint16_t rc_shared;
int ledpin = 12;
int minLimit = 900;
int maxLimit = 1450;
int buffer_enable_pin = 13;

void rc_read_values() {
    noInterrupts();
    //memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
    rc_values=rc_shared;
    interrupts();
}

void calc_input() {
    if (digitalRead(RC_CH4_INPUT) == HIGH) {
        rc_start = micros();
    } else {
        uint16_t rc_compare = (uint16_t)(micros() - rc_start);
        rc_shared = rc_compare;
    }
}


void setup() {
    Serial.begin(SERIAL_PORT_SPEED);

    pinMode(RC_CH4_INPUT, INPUT);
    enableInterrupt(RC_CH4_INPUT, calc_input, CHANGE);
    pinMode(ledpin,OUTPUT );
    pinMode (buffer_enable_pin,OUTPUT );
}

void loop() {

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
        digitalWrite (buffer_enable_pin, LOW);
    }else{
        digitalWrite(ledpin,LOW);
        digitalWrite (buffer_enable_pin, HIGH);
    }
    delay (500);

}
