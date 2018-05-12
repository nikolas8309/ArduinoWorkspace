#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>

#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"

#include "utilities.h"

void printFloat(double number, int digits=2);

TinyGPS gps;
SoftwareSerial nss(6,7);//2,3
LSM303C myIMU;

const int setWaypointButtonPin = 5;

void setup()
{
	pinMode(setWaypointButtonPin , INPUT);

	Serial.begin(115200);
//	nss.begin(9600);
  
  //for receiver read 
   pinMode(RC_CH4_INPUT, INPUT);
   attachInterrupt(digitalPinToInterrupt(RC_CH4_INPUT), calc_input, CHANGE);

//  
//	if (myIMU.begin() != IMU_SUCCESS)
//	{
//		Serial.println("Failed setup magneto");
//		while(1);
//	}

	Wire.begin();
}

void loop()
{
  if (!hasSignal()) {
    Serial.println ("xathike to sima");
  }
    else {Serial.println ("vrethike to sima");
    }
//       
//  static Point point2;
//  Point point1;
//
//  
//	if(checkSetWaypointButton()){//to koumpi exei patithei
//		//diavase tis sintetagmenes apo to gps kai valtes sto Point2
//    Serial.println("Setting waypoint");
//		gps.f_get_position(&point2.latitude, &point2.longitude);
//	}
// 
//	gps.f_get_position(&point1.latitude, &point1.longitude);
//
//	bool newdata = false;
//	unsigned long start = millis();
//	// Every fourth of a second we print an update
//
//	while (millis() - start < 250)
//	{
//		if (feedgps())//returns true if new data is available
//		newdata = true;
//	}
//	if (newdata)
//	{
//		Serial.println("Acquired Data");
//		Serial.println("-------------");
//		gpsdump(gps); //dumps data in STDOUT
//
//    float dist=distance(point1,point2);
//    Serial.print("distance: ");
//    Serial.print(dist,4);    //print the distance in meters
//    Serial.println(" m");
//  
//    float heading=headingf(point1,point2);
//    Serial.print("heading: ");
//    Serial.print(heading);   // print the heading.
//    Serial.println(" degrees");
//  
//      
//    //compassread();
//
//		Serial.println("-------------");
//		Serial.println();
//	}
}



