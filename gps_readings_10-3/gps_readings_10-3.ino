#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>

#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"

void printFloat(double number, int digits=2);

TinyGPS gps;
SoftwareSerial nss(2, 3);
LSM303C myIMU;

const int setWaypointButtonPin = 5;

void setup()
{
	pinMode(setWaypointButtonPin , INPUT);

	Serial.begin(115200);
	nss.begin(9600);

	if (myIMU.begin() != IMU_SUCCESS)
	{
		Serial.println("Failed setup magneto");
		while(1);
	}

	Wire.begin();
}

void loop()
{
  static float flat2;
  static float flon2;
  float flat, flon;
  
	if(checkSetWaypointButton()){//to koumpi exei patithei
		//diavase tis sintetagmenes apo to gps kai valtes
		//sthn RAM san flat2 kai flon2
    Serial.println("Setting waypoint");
		gps.f_get_position(&flat2, &flon2 );
	}
 
	gps.f_get_position(&flat, &flon);
	//Serial.println("MARK1");
	//printDistanceDifference(flat,flon,flat2,flon2);
	//Serial.println("MARK2");

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

    float dist=distance(flat,flon,flat2,flon2);
    Serial.println("distance");
    Serial.print(dist,4);    //print the distance in meters
    Serial.println(" m");
  
    headingf();
    
    compassread();

		Serial.println("-------------");
		Serial.println();
	}



}











