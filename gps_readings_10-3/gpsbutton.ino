
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



