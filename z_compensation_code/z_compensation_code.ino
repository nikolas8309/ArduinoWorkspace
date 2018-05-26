
//code by Arne
//the acclerometer it set up the way that the z acceleration looks
//to the sky, and x y is flat --> like most cartesian coordinate systems
//I use an A7270 as an Accelerometer -> they are on a breakout board for approx $20 USD
//and a HMC5843 as a triple axis magnetic Sensor $50 USD
//feel free to comment on the code -> improvement is always appreciated
//you can ask questions in English or German

//required for calculations
#include <math.h>
//required for HMC5843 communication
#include <HMC.h>



//accelerometer connecteded to pins 0 through 2
#define xAxis 0 
#define yAxis 1
#define zAxis 2



//by increasing alphaAccel the response will become faster
//but the noise will increae [alpha must be between 0 and 1]
//values for digital lowpass
float alphaAccel = 0.4;
float alphaMagnet = 0.4;

unsigned int xOffset=0;
unsigned int yOffset=0;
unsigned int zOffset=0;

float Pitch=0;
float Roll=0;
float Yaw=0;

int xRaw=0;
int yRaw=0;
int zRaw=0;

float xFiltered=0;
float yFiltered=0;
float zFiltered=0;

float xFilteredOld=0;
float yFilteredOld=0;
float zFilteredOld=0;

float xAccel=0;
float yAccel=0;
float zAccel=0;

int xMagnetRaw=0;
int yMagnetRaw=0;
int zMagnetRaw=0;

float xMagnetFiltered=0;
float yMagnetFiltered=0;
float zMagnetFiltered=0;

float xMagnetFilteredOld=0;
float yMagnetFilteredOld=0;
float zMagnetFilteredOld=0;

int xMagnetMax=0;
int yMagnetMax=0;
int zMagnetMax=0;

int xMagnetMin=10000;
int yMagnetMin=10000;
int zMagnetMin=10000;

float xMagnetMap=0;
float yMagnetMap=0;
float zMagnetMap=0;

float YawU;

//initialize µController
void setup()
{
 Serial.begin(115200);       //initialize serial port
 analogReference(EXTERNAL);  //use external reference voltage (3,3V)
 delay(2000);  //calibrate sensor after a short delay
 HMC.init();
 getAccelOffset();           //keep it flat and non moving on the table

 //there are other ways to calibrate the offset, each has some advantes
 //and disadvantes..
 //compare application note AN3447
 //http://www.freescale.com/files/sensors/doc/app_note/AN3447.pdf
}


void FilterAD()
{
 // read from AD and subtract the offset
 xRaw=analogRead(xAxis)-xOffset;
 yRaw=analogRead(yAxis)-yOffset;
 zRaw=analogRead(zAxis)-zOffset;
 
 //Digital Low Pass - compare: (for accelerometer)
 //http://en.wikipedia.org/wiki/Low-pass_filter
 xFiltered= xFilteredOld + alphaAccel * (xRaw - xFilteredOld);
 yFiltered= yFilteredOld + alphaAccel * (yRaw - yFilteredOld);
 zFiltered= zFilteredOld + alphaAccel * (zRaw - zFilteredOld);
 
 xFilteredOld = xFiltered;
 yFilteredOld = yFiltered;
 zFilteredOld = zFiltered;
 
 
 
 //read from Compass
 //Digital Low Pass for Noise Reduction for Magnetic Sensor
 HMC.getValues(&xMagnetRaw,&yMagnetRaw,&zMagnetRaw);
 
 xMagnetFiltered= xMagnetFilteredOld + alphaMagnet * (xMagnetRaw - xMagnetFilteredOld);
 yMagnetFiltered= yMagnetFilteredOld + alphaMagnet * (yMagnetRaw - yMagnetFilteredOld);
 zMagnetFiltered= zMagnetFilteredOld + alphaMagnet * (zMagnetRaw - zMagnetFilteredOld);
 
 xMagnetFilteredOld = xMagnetFiltered;
 yMagnetFilteredOld = yMagnetFiltered;
 zMagnetFilteredOld = zMagnetFiltered;
   
}
 

void AD2Degree()
{ 
 // 3.3 = Vref; 1023 = 10Bit AD; 0.8 = Sensivity Accelerometer
 // (compare datasheet of your accelerometer)
 // the *Accel must be between -1 and 1; you may have to
 // to add/subtract +1 depending on the orientation of the accelerometer
 // (like me on the zAccel)
 // they are not necessary, but are useful for debugging
 xAccel=xFiltered *3.3 / (1023.0*0.8);       
 yAccel=yFiltered *3.3 / (1023.0*0.8);       
 zAccel=zFiltered *3.3 / (1023.0*0.8)+1.0;
 
 // Calculate Pitch and Roll (compare Application Note AN3461 from Freescale
 // http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf
 // Microsoft Excel switches the values for atan2
 // -> this info can make your life easier :-D
 //angled are radian, for degree (* 180/3.14159)
 Roll   = atan2(  yAccel ,  sqrt(sq(xAccel)+sq(zAccel)));  
 Pitch  = atan2(  xAccel ,   sqrt(sq(yAccel)+sq(zAccel)));
  
}

void getAzimuth()
{
 //this part is required to normalize the magnetic vector
 if (xMagnetFiltered>xMagnetMax) {xMagnetMax = xMagnetFiltered;}
 if (yMagnetFiltered>yMagnetMax) {yMagnetMax = yMagnetFiltered;}
 if (zMagnetFiltered>zMagnetMax) {zMagnetMax = zMagnetFiltered;}
 
 if (xMagnetFiltered<xMagnetMin) {xMagnetMin = xMagnetFiltered;}
 if (yMagnetFiltered<yMagnetMin) {yMagnetMin = yMagnetFiltered;}
 if (zMagnetFiltered<zMagnetMin) {zMagnetMin = zMagnetFiltered;}
 
 float norm;
 
 xMagnetMap = float(map(xMagnetFiltered, xMagnetMin, xMagnetMax, -10000, 10000))/10000.0;
 yMagnetMap = float(map(yMagnetFiltered, yMagnetMin, yMagnetMax, -10000, 10000))/10000.0;
 zMagnetMap = float(map(zMagnetFiltered, zMagnetMin, zMagnetMax, -10000, 10000))/10000.0;
 

//normalize the magnetic vector
norm= sqrt( sq(xMagnetMap) + sq(yMagnetMap) + sq(zMagnetMap));
xMagnetMap /=norm;
yMagnetMap /=norm;
zMagnetMap /=norm;
 
//compare Applications of Magnetic Sensors for Low Cost Compass Systems by Michael J. Caruso
//for the compensated Yaw equations...
//http://www.ssec.honeywell.com/magnetic/datasheets/lowcost.pdf
Yaw=atan2( (-yMagnetMap*cos(Roll) + zMagnetMap*sin(Roll) ) , xMagnetMap*cos(Pitch) + zMagnetMap*sin(Pitch)*sin(Roll)+ zMagnetMap*sin(Pitch)*cos(Roll)) *180/PI;
YawU=atan2(-yMagnetMap, xMagnetMap) *180/PI;
}


void loop()
{
 FilterAD();
 AD2Degree();
 getAzimuth();
 Send2Com();
} 

void Send2Com()
{
 Serial.print("Pitch: ");
 Serial.print(int(Pitch*180/PI));
 Serial.print(" Roll: ");
 Serial.print(int(Roll*180/PI));

 Serial.print(" Yaw: ");
 Serial.print(int(Yaw));

 Serial.print(" YawU: ");
 Serial.println(int(YawU));
 delay(50);
}
 



void getAccelOffset()
{ //you can make approx 60 iterations because we use an unsigned int 
 //otherwise you get an overflow. But 60 iterations should be fine
  for (int i=1; i <= 60; i++){        
    xOffset += analogRead(xAxis);     
    yOffset += analogRead(yAxis);
    zOffset += analogRead(zAxis);
    } 
  xOffset /=60;   
  yOffset /=60;
  zOffset /=60;

  Serial.print("xOffset: ");
  Serial.print(xOffset);
  Serial.print("   yOffset: ");
  Serial.print(yOffset);
  Serial.print("   zOffset: ");
  Serial.println(zOffset);
}

