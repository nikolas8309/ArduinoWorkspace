#include <NewSoftSerial.h>
#include <TinyGPS.h>  
#include <Wire.h>
int HMC6352Address = 0x42;
int slaveAddress;
byte headingData[2];
int i, headingValue;
     // tiny gps library code
  float flat, flon;
   float heading=0;
int headinggps;
TinyGPS gps;
NewSoftSerial nss(2, 3);    // rx and tx pins in use
#define mo1 5
#define mo2 4
#define mo3 6
#define mo4 7
int x4=0;
#define waypoints 5   // number of waypoints
int waycont=1;
float x2lat;
float x2lon;
float flat2=28.34140014;   //waypoint 1    //28.324603,-82.267419 home testing
float flon2=-82.27369689;
float flat3=28.3415508;        //waypoint 2
float flon3=-82.2736816;
float flat4=28.3415794;       //waypoint 3
float flon4=-82.2741317;
float flat5=28.3414192;     // waypoint   4
float flon5=-82.2741470;
float flat6 = 28.3413600;
float flon6 =-82.2739028;
void gpsdump(TinyGPS &gps);
bool feedgps();
void printFloat(double f, int digits = 2);
int serv;
void setup()
{
  slaveAddress = HMC6352Address >> 1;  
Wire.begin();
  Serial.begin(115200);
  nss.begin(4800);
pinMode(mo1, OUTPUT);
    pinMode(mo2, OUTPUT);
      pinMode(mo3,OUTPUT);
        pinMode(mo4, OUTPUT);
}

void loop()
{ //-------------------------------------------- this is all gps stuff. This is just the example code given from tiny gps library.
//----------------------------------------------I deleted the part of the code for the time and date. I did not want it.

  bool newdata = false;
  unsigned long start = millis();
  while (millis() - start < 250)            // get new data every 1/4 of a second
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

void printFloat(double number, int digits)
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

  unsigned long age, date, time, chars;

  unsigned short sentences, failed;

  
  feedgps(); // If we don't feed the gps during this long routine, we may drop characters and get checksum errors

  gps.f_get_position(&flat, &flon, &age);
  Serial.print("Lat/Long(float): "); printFloat(flat, 7); Serial.print(", "); printFloat(flon, 7);   // print our current posistion
  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");

   feedgps();
    Serial.print("Alt(cm): "); Serial.print(gps.altitude()); Serial.print(" Course(10^-2 deg): "); Serial.print(gps.course()); Serial.print(" Speed(10^-2 knots): "); Serial.println(gps.speed());
  Serial.print("Alt(float): "); printFloat(gps.f_altitude()); Serial.print(" Course(float): "); printFloat(gps.f_course()); Serial.println();
  Serial.print("Speed(knots): "); printFloat(gps.f_speed_knots()); Serial.print(" (mph): ");  printFloat(gps.f_speed_mph());
  Serial.print(" (mps): "); printFloat(gps.f_speed_mps()); Serial.print(" (kmph): "); printFloat(gps.f_speed_kmph()); Serial.println();
float speedy=gps.f_speed_knots();
feedgps();

  gps.stats(&chars, &sentences, &failed);
  Serial.print("Stats: characters: "); Serial.print(chars); Serial.print(" sentences: "); Serial.print(sentences); Serial.print(" failed checksum: "); Serial.println(failed);
distance();
}
  
bool feedgps()
{
  while (nss.available())
  {
    if (gps.encode(nss.read()))
      return true;
  }
  return false;
}
//------------------------------below is the part of the code where everything is calculated
void distance(){
  if(waycont==1){
 x2lat = flat2;      // setting x2lat and x2lon equal to our first waypoint
 x2lon = flon2;   
  }
  if(waycont==2){
    x2lat = flat3;
    x2lon = flon3;
  }
  if(waycont==3){
    x2lat = flat4;
    x2lon = flon4;
  }
  if(waycont==4){
  x2lat = flat5;
  x2lon = flon5;
  }
   if(waycont==5){
  x2lat = flat6;
  x2lon = flon6;
  }
 

 float flat1=flat;            
 float flon1=flon;
float dist_calc=0;
float dist_calc2=0;
float diflat=0;
float diflon=0;

//------------------------------------------ distance formula below. Calculates distance from current location to waypoint
diflat=radians(x2lat-flat1);  //notice it must be done in radians
flat1=radians(flat1);
x2lat=radians(x2lat);
diflon=radians((x2lon)-(flon1));

dist_calc = (sin(diflat/2.0)*sin(diflat/2.0));
dist_calc2= cos(flat1);
dist_calc2*=cos(x2lat);
dist_calc2*=sin(diflon/2.0);                                       
dist_calc2*=sin(diflon/2.0);
dist_calc +=dist_calc2;

dist_calc=(2*atan2(sqrt(dist_calc),sqrt(1.0-dist_calc)));

dist_calc*=6371000.0; //Converting to meters
Serial.println("distance");
Serial.println(dist_calc);
if(dist_calc<4){
if(waycont==waypoints){
  done();
}
waycont+=1;
}
//-----------------------------------------heading formula below. Calculates heading to the waypoint from the current locaiton
 flon1 = radians(flon1);  //also must be done in radians
 x2lon = radians(x2lon);

heading = atan2(sin(x2lon-flon1)*cos(x2lat),cos(flat1)*sin(x2lat)-sin(flat1)*cos(x2lat)*cos(x2lon-flon1)),2*3.1415926535;
heading = heading*180/3.1415926535;  // convert from radians to degrees
int head =heading; 
if(head<0){
  heading+=360;   //if the heading is negative then add 360 to make it positive
}

Serial.println("heading:");
Serial.println(heading);
//-------------------------------------------------------------

int turn=0;
 Wire.beginTransmission(slaveAddress);        //the wire stuff is for the compass module
  Wire.send("A");              
  Wire.endTransmission();
  delay(10);                  
  Wire.requestFrom(slaveAddress, 2);       
  i = 0;
  while(Wire.available() && i < 2)
  { 
    headingData[i] = Wire.receive();
    i++;
  }
  headingValue = headingData[0]*256 + headingData[1];
 int pracheading = headingValue / 10;      // this is the heading of the compass
 if(pracheading>0){
   headinggps=pracheading;
 }
Serial.println("current heaDING:");
Serial.println(headinggps);
x4=headinggps-heading;   //getting the difference of our current heading to our needed heading
float absolute= abs(x4);    //we will use this for our delay when turning
if(absolute>180){
  absolute-=180;        //we only want 0 - 180
}
//Serial.println(absolute);

int x5;

//-------------------------------------- below tells us which way we need to turn
if(x4>=-180){
  if(x4<=0){
    turn=8;    //set turn =8 which means "right"         
  }
}
if(x4<-180){
  turn=5;      //set turn = 5 which means "left"
}
if(x4>=0){
  if(x4<180){
    turn=5;   //set turn = 5 which means "left"
  }
}
if(x4>=180){     //set turn =8 which means "right"
  turn=8;
}
//-----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------real important turning stuff. DO NOT TOUCH!!!
float hd = headinggps;
if(hd==heading){
    turn=3;   //then set turn = 3 meaning go "straight"
 
}

if(turn==3){
 
  Serial.println("straight");
digitalWrite(mo1, LOW);               //go straight 
    digitalWrite(mo2, HIGH);
      digitalWrite(mo3, LOW);
        digitalWrite(mo4, LOW);
  

}
//-------------------------------------------------------------------------------------turn right
if(turn==8){
rightturn();

}
//------------------------------------------------------------------------------------------turn left

if(turn==5){
leftturn();
}



 //-------------------------------------------------------------------------
}

  

void done(){
  
  digitalWrite(mo1, LOW);   
    digitalWrite(mo2, LOW);
      digitalWrite(mo3, LOW);
        digitalWrite(mo4, LOW);
      done();
}
//----------------------------------------------------------------------------------
//---------------------------------------------------------------------------
//------------------------------------------------------right turning
void rightturn(){
if(headinggps+2>heading){
  if(headinggps-2<heading){
      digitalWrite(mo3, LOW);
        digitalWrite(mo4, LOW);
    return;
  }
}
      x4=headinggps-heading;  
if(x4<-180){
return;
}
if(x4>=0){
  if(x4<180){
  return;
  }
}

  digitalWrite(mo1, LOW);
    digitalWrite(mo2, HIGH);   
      digitalWrite(mo3, HIGH);
        digitalWrite(mo4, LOW); 
         Wire.beginTransmission(slaveAddress);        //the wire stuff is for the compass module
  Wire.send("A");              
  Wire.endTransmission();
  delay(10);                  
  Wire.requestFrom(slaveAddress, 2);       
  i = 0;
  while(Wire.available() && i < 2)
  { 
    headingData[i] = Wire.receive();
    i++;
  }
  headingValue = headingData[0]*256 + headingData[1];  
headinggps = headingValue / 10;      // this is the heading of the compass
rightturn();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------
//----------------------------------------------left turning
void leftturn(){
  if(headinggps+2>heading){
  if(headinggps-2<heading){
      digitalWrite(mo3, LOW);
        digitalWrite(mo4, LOW);
    return;
  }
}
      x4=headinggps-heading;  
if(x4>=-180){
  if(x4<=0){
     return;         
  }
}

if(x4>=180){     
  return;
}

digitalWrite(mo1, LOW);
    digitalWrite(mo2, HIGH);
      digitalWrite(mo3, LOW);
        digitalWrite(mo4, HIGH); 
         Wire.beginTransmission(slaveAddress);        //the wire stuff is for the compass module
  Wire.send("A");              
  Wire.endTransmission();
  delay(10);                  
  Wire.requestFrom(slaveAddress, 2);       
  i = 0;
  while(Wire.available() && i < 2)
  { 
    headingData[i] = Wire.receive();
    i++;
  }
  headingValue = headingData[0]*256 + headingData[1];  
headinggps = headingValue / 10;      // this is the heading of the compass
leftturn();
}
