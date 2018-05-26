#include <TinyGPS.h>
#include <Wire.h>
#include "utilities.h"

//------------azimuth for teensy staff
union { 
    int16_t i; 
    uint16_t u;
} Converter;

//----------------

void printFloat(double number, int digits=2);

TinyGPS gps;
MechaQMC5883 qmc;

const int setWaypointButtonPin = 6;

Servo myservo;
Servo esc;

void setup()
{
    Serial.begin(115200);
    Serial.println("START");

    pinMode(setWaypointButtonPin , INPUT);
    pinMode (TO_BUFFER_PIN ,OUTPUT);

    //servo staff
    myservo.attach (ARDUINO_TO_DIRECTION_SERVO_PIN);
    esc.attach (ARDUINO_TO_ESC_PIN);


    
    GPS_SERIAL_PORT.begin(9600);

    //for receiver read 
    pinMode(RC_CH4_INPUT, INPUT);
    attachInterrupt(digitalPinToInterrupt(RC_CH4_INPUT), calc_input, CHANGE);

    Wire.begin();

    qmc.init();

    //make sure receiver has the control
    setControlHolder(RECEIVER);


    
}


void loop()
{
    //TEST
    Serial.print("expected 10 - result= ");Serial.println(foivos(40,50));
    Serial.print("expected 10 - result= ");Serial.println(foivos(355,5));
    Serial.print("expected 20 - result= ");Serial.println(foivos(10,350));
    Serial.print("expected 179 - result= ");Serial.println(foivos(181,0));

    static Point wayPoint;
    Point currentPoint;

    if (hasSignal()) {
        setControlHolder (RECEIVER); 
    }
    else {
        setControlHolder (MICROCONTROLLER);
        setThrottle(100);

        //---------------------------------------------------get current point 
        currentPoint = getGpsCurrentPosition ();

        // ------------------------------------------------------------ update waypoint if button was pressed
        if(checkSetWaypointButton()){//to koumpi exei patithei
            //diavase tis sintetagmenes apo to gps kai valtes sto waypoint
            gps.f_get_position(&wayPoint.latitude, &wayPoint.longitude);
        }
        gpsdump(gps);  
        //-------------------------------------------------get waypoint heading (desired heading)
        int desiredHeading=headingInt(currentPoint,wayPoint);
        Serial.print("desired heading: ");
        Serial.print(desiredHeading);   // print the heading.
        Serial.println(" degrees");
        
        //----------------------------------------------------get current heading
        int currentHeading = getAzimuth();
        Serial.print("current heading:");
        Serial.println(currentHeading);

        

        //-------------------------------get distance between current point and waypoint for debugging
//        float dist=distance(currentPoint,wayPoint);
//        Serial.print("distance: ");
//        Serial.print(dist,4);    //print the distance in meters
//        Serial.println(" m");

       
        
        //check if they are equal
        if( lookSameDirection( desiredHeading, currentHeading)){
              Serial.println ("koitane stin idia");
        }
        else 
              Serial.println ("den koitane stin idia");
        //set direction
        //    setDirection();

        delay(2000);
    }
    
}//end loop


