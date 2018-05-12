
/*-----( Import needed libraries )-----*/
#include <OneWire.h>
#include <DallasTemperature.h>
/*-----( Declare Constants )-----*/
#define ONE_WIRE_BUS 4 /*-(Connect to Pin 2 )-*/

/*-----( Declare objects )-----*/
/* Set up a oneWire instance to communicate with any OneWire device*/
OneWire ourWire(ONE_WIRE_BUS);

/* Tell Dallas Temperature Library to use oneWire Library */
DallasTemperature sensors(&ourWire);


void setup(void)
{


  Serial.begin(9600);   
  sensors.begin();

  
}

void loop(void)
{

    sensors.requestTemperatures();
    float t=sensors.getTempCByIndex(0);
    Serial.print(" t= ");
    Serial.print(t);

}


