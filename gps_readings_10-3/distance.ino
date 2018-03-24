
// ypologizei kai epistrefei tin apostash metaksi dyo simeion (se metra)
float distance(float flat1, float flon1, float  flat2, float  flon2){      

	float dist_calc=0;
	float dist_calc2=0;
	float diflat=0;
	float diflon=0;

	//------------------------------------------ distance formula below. Calculates distance from current location to waypoint

	diflat=radians(flat2-flat1);  //notice it must be done in radians
	flat1=radians(flat1);    //convert current latitude to radians
	flat2=radians(flat2);  //convert waypoint latitude to radians
	diflon=radians((flon2)-(flon1));   //subtract and convert longitudes to radians
	dist_calc = (sin(diflat/2.0)*sin(diflat/2.0));
	dist_calc2= cos(flat1);
	dist_calc2*=cos(flat2);
	dist_calc2*=sin(diflon/2.0);                                       
	dist_calc2*=sin(diflon/2.0);
	dist_calc +=dist_calc2;
	dist_calc=(2*atan2(sqrt(dist_calc),sqrt(1.0-dist_calc)));
	dist_calc*=6371000.0; //Converting to meters
	
	return dist_calc;
	
}
