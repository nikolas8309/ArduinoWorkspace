#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <Arduino.h>
#include <Wire.h>
#include <MechaQMC5883.h>
#include <Servo.h>

#define RC_CH4_INPUT  2

#define TO_BUFFER_PIN 12 

#define SERVO_CENTER 90
#define SERVO_RIGHT 170
#define SERVO_LEFT 10

#define FULL_THROTTLE 100
#define ZERO_THROTTLE 0

#define ARDUINO_TO_DIRECTION_SERVO_PIN 9
#define ARDUINO_TO_ESC_PIN 10


#define GPS_SERIAL_PORT Serial1

struct Point {
   float latitude;
   float longitude;
};


enum DIRECTION { LEFT,RIGHT,CENTER};

enum CONTROLHOLDER {RECEIVER, MICROCONTROLLER};


#endif

