
//ypologizei kai typonei to heading apo to ena simeio sto allo
void headingf()
{
//  Serial.print("flon1=");
//  Serial.print(flon1);
//  Serial.print("flat1=");
//  Serial.print(flat1);
//  Serial.print(" x2lon=");
//  Serial.print(x2lon);
//  Serial.print("x2lat=");
//  Serial.println(x2lat);
  
	flon1 = radians(flon1);  //also must be done in radians

	x2lon = radians(x2lon);  //radians duh.

	heading = atan2(sin(x2lon-flon1)*cos(x2lat),cos(flat1)*sin(x2lat)-sin(flat1)*cos(x2lat)*cos(x2lon-flon1)),2*3.1415926535;

	heading = heading*180/3.1415926535;  // convert from radians to degrees

	int head =heading; //make it a integer now

	if(head<0){

		heading+=360;   //if the heading is negative then add 360 to make it positive

	}

	Serial.println("heading:");

	Serial.println(heading);   // print the heading.
}
