

bool checkSetWaypointButton ()
{

	buttonState = digitalRead(setWaypointPin);
	if (buttonState == HIGH)
    return true;
  else
    return false;

  


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

static void print_float(float val, float invalid, int len, int prec)
{
	if (val == invalid)
	{
		while (len-- > 1)
		Serial.print('*');
		Serial.print(' ');
	}
	else
	{
		Serial.print(val, prec);
		int vi = abs((int)val);
		int flen = prec + (val < 0.0 ? 2 : 1); // . and -
		flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
		for (int i=flen; i<len; ++i)
		Serial.print(' ');
	}
	smartdelay(0);
}

static void print_int(unsigned long val, unsigned long invalid, int len)
{
	char sz[32];
	if (val == invalid)
	strcpy(sz, "*******");
	else
	sprintf(sz, "%ld", val);
	sz[len] = 0;
	for (int i=strlen(sz); i<len; ++i)
	sz[i] = ' ';
	if (len > 0) 
	sz[len-1] = ' ';
	Serial.print(sz);
	smartdelay(0);
}

static void print_date(TinyGPS &gps)
{
	int year;
	byte month, day, hour, minute, second, hundredths;
	unsigned long age;
	gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
	if (age == TinyGPS::GPS_INVALID_AGE)
	Serial.print("********** ******** ");
	else
	{
		char sz[32];
		sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
		month, day, year, hour, minute, second);
		Serial.print(sz);
	}
	print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
	smartdelay(0);
}

static void print_str(const char *str, int len)
{
	int slen = strlen(str);
	for (int i=0; i<len; ++i)
	Serial.print(i<slen ? str[i] : ' ');
	smartdelay(0);
}



