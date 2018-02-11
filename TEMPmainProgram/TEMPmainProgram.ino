#include <Ethernet.h>
#include <HttpClient.h>
#include "ThingSpeak.h"
#include <Wire.h>
#include "SparkFunHTU21D.h"



// MAC address for your Ethernet shield
byte mac[] = { 0x85, 0x4E, 0xD2, 0x21, 0x57, 0x18 };

EthernetClient client;

//-------- Thingspeak STUFF -----------------------

unsigned long myChannelNumber = 174299;
const char * myWriteAPIKey = "EMCQJ13A6A1D6CCQ";

//-------------------------------------------
//Create an instance of the object
HTU21D myHumidity;

void setup() {
    Serial.begin(9600);
    myHumidity.begin();
}

void loop() {
  

}

