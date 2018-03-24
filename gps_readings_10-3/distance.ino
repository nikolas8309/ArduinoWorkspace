

void distance(){      //this function will do all the calculations
	flat1=flat;     // flat1 = our current latitude. flat is from the gps data. 
	flon1=flon;  // flon1 = our current longitude. flon is from the fps data.
	float dist_calc=0;
	float dist_calc2=0;
	float diflat=0;
	float diflon=0;
	x2lat=flat2 ;  //enter a latitude point here   this is going to be your waypoint
  x2lon=flon2 ;  // enter a longitude point here  this is going to be your waypoint

	//------------------------------------------ distance formula below. Calculates distance from current location to waypoint

	diflat=radians(x2lat-flat1);  //notice it must be done in radians
	flat1=radians(flat1);    //convert current latitude to radians
	x2lat=radians(x2lat);  //convert waypoint latitude to radians
	diflon=radians((x2lon)-(flon1));   //subtract and convert longitudes to radians
	dist_calc = (sin(diflat/2.0)*sin(diflat/2.0));
	dist_calc2= cos(flat1);
	dist_calc2*=cos(x2lat);
	dist_calc2*=sin(diflon/2.0);                                       
	dist_calc2*=sin(diflon/2.0);
	dist_calc +=dist_calc2;
	dist_calc=(2*atan2(sqrt(dist_calc),sqrt(1.0-dist_calc)));
	dist_calc*=6371000.0; //Converting to meters
	Serial.println("distance");
	Serial.print(dist_calc);    //print the distance in meters
  Serial.println(" m");
	
	headingf();
	compassread();
}
