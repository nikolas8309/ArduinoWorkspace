
/**
 * epistrefei true sthn metavash apo low se high
 * epistrefei false sthn metavash apo high se low
 */
bool checkSetWaypointButton ()
{
  bool buttonState;
  static bool previousState = false;
  
  buttonState = digitalRead(setWaypointButtonPin);

  
  if(buttonState==HIGH && previousState==LOW){//patima
    previousState=buttonState;
    return true;
  }
  
  else{ //se kathe alli periptosi
    previousState=buttonState;
    return false;
  }
}

void printDistanceDifference(float flat,float flon,float  flat2,float  flon2){
  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
  print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
  //typose thn diafora se metra ton flat2 kai flon2 me tis torines suntetagmenes
  print_int(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0xFFFFFFFF : (unsigned long)TinyGPS::distance_between(flat, flon, flat2, flon2) / 1, 0xFFFFFFFF, 9);
  print_float(flat == TinyGPS::GPS_INVALID_F_ANGLE ? TinyGPS::GPS_INVALID_F_ANGLE : TinyGPS::course_to(flat, flon, flat2, flon2), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2);
  Serial.println();
  ;
  smartdelay(1000);
}

/**
 * Delay while keeping track of gps activity
 */
static void smartdelay(unsigned long ms)
{
	unsigned long start = millis();
	do 
	{
		while (nss.available())
		gps.encode(nss.read());
	} while (millis() - start < ms);
}



