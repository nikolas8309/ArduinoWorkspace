#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>

#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"

//int HMC6352Address = 0x1E;
//int slaveAddress; //TODO check if it is used anywhere
byte headingData[2];
int i, headingValue;
float flat2, flon2;
float flat, flon;
float flat1;
float flon1;
float heading;
float x2lat;
float x2lon ;
int headingcompass;

TinyGPS gps;
SoftwareSerial nss(2, 3);
LSM303C myIMU;

//void gpsdump(TinyGPS &gps);
//bool feedgps();
//void printFloat(double f, int digits = 2);
//void gpsbutton (); 
//void headingf();
//void compassread();
int staticlocation = 5;
int buttonstate = 0;

void setup()
{
	pinMode(staticlocation , INPUT);

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
	gpsbutton ();
	bool newdata = false;
	unsigned long start = millis();
	// Every fourth of a second we print an update

	while (millis() - start < 250)
	{
		if (feedgps())
		newdata = true;
	}
	if (newdata)
	{
		Serial.println("Acquired Data");
		Serial.println("-------------");
		gpsdump(gps);
		Serial.println("-------------");
		Serial.println();
	}



}

void printFloat(double number, int digits=2)
{
	// Handle negative numbers
	if (number < 0.0)
	{
		Serial.print('-');
		number = -number;
	}

	// Round correctly so that print(1.999, 2) prints as "2.00"
	double rounding = 0.5;
	for (uint8_t i=0; i<digits; ++i)
	rounding /= 10.0;

	number += rounding;

	// Extract the integer part of the number and print it
	unsigned long int_part = (unsigned long)number;
	double remainder = number - (double)int_part;
	Serial.print(int_part);

	// Print the decimal point, but only if there are digits beyond
	if (digits > 0)
	Serial.print("."); 

	// Extract digits from the remainder one at a time
	while (digits-- > 0)
	{
		remainder *= 10.0;
		int toPrint = int(remainder);
		Serial.print(toPrint);
		remainder -= toPrint; 
	} 
}

void gpsdump(TinyGPS &gps)
{
	long lat, lon;
	float flat, flon;
	unsigned long age, date, time, chars;
	unsigned short sentences, failed;

	gps.get_position(&lat, &lon, &age);
	Serial.print("Lat/Long(10^-5 deg): "); Serial.print(lat); Serial.print(", "); Serial.print(lon); 
	Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");

	feedgps(); // If we don't feed the gps during this long routine, we may drop characters and get checksum errors

	gps.f_get_position(&flat, &flon, &age);
	Serial.print("Lat/Long(float): "); printFloat(flat, 5); Serial.print(", "); printFloat(flon, 5);
	Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");

	feedgps();

	gps.stats(&chars, &sentences, &failed);
	Serial.print("Stats: characters: "); Serial.print(chars); Serial.print(" sentences: "); Serial.print(sentences); Serial.print(" failed checksum: "); Serial.println(failed);

	distance();
}







