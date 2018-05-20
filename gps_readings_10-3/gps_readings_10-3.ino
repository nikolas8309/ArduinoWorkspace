//#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>

//#include "SparkFunIMU.h"
//#include "SparkFunLSM303C.h"
//#include "LSM303CTypes.h"

#include "utilities.h"

void printFloat(double number, int digits=2);

TinyGPS gps;
//SoftwareSerial nss(6,7);//2,3
MechaQMC5883 qmc;

const int setWaypointButtonPin = 5;

Servo myservo;
Servo esc;
void setup()
{
	pinMode(setWaypointButtonPin , INPUT);
  pinMode (NANO_OUT_PIN , INPUT);
  pinMode (TO_BUFFER_PIN ,OUTPUT);

//servo staff
  myservo.attach (ARDUINO_TO_DIRECTION_SERVO_PIN);
  esc.attach (ARDUINO_TO_ESC_PIN);
  
	Serial.begin(115200);
	//nss.begin(9600);
  GPS_SERIAL_PORT.begin(9600);
  
  //for receiver read 
//   pinMode(RC_CH4_INPUT, INPUT);
//   attachInterrupt(digitalPinToInterrupt(RC_CH4_INPUT), calc_input, CHANGE);
   
    qmc.init();

	Wire.begin();

 //make sure receiver has the control
 //setControlHolder(RECEIVER);
}

void loop()
{
  static Point wayPoint;
  Point currentPoint;
  
  if (hasSignal()) {
    setControlHolder (RECEIVER);
}
  else {
    setControlHolder (ARDUINO);
    setThrottle(100);

    //get current point 
    currentPoint = getGpsCurrentPosition ();

    //  update waypoint if button was pressed
    if(checkSetWaypointButton()){//to koumpi exei patithei
      //diavase tis sintetagmenes apo to gps kai valtes sto waypoint
      gps.f_get_position(&wayPoint.latitude, &wayPoint.longitude);
    }
        
    //get waypoint heading
    float heading=headingf(currentPoint,wayPoint);
    
    //get current heading
    int currentHeading = getAzimuth();
    Serial.print(currentHeading);

    //check if they are equal

    //set direction
//    setDirection();
    
    }
//-0------------------------------

       


  

 


	bool newdata = false;
	unsigned long start = millis();
	// Every fourth of a second we print an update

	while (millis() - start < 250)
	{
		if (feedgps())//returns true if new data is available
		newdata = true;
	}
	if (newdata)
	{
		Serial.println("Acquired Data");
		Serial.println("-------------");
		gpsdump(gps); //dumps data in STDOUT

    float dist=distance(currentPoint,wayPoint);
    Serial.print("distance: ");
    Serial.print(dist,4);    //print the distance in meters
    Serial.println(" m");
  
    float heading=headingf(currentPoint,wayPoint);
    Serial.print("heading: ");
    Serial.print(heading);   // print the heading.
    Serial.println(" degrees");
  
      
    

		Serial.println("-------------");
		Serial.println();
	}
}



