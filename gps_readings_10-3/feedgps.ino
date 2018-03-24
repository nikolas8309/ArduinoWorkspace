
/**
* 	returns true if new data is available, otherwise false
*/
bool feedgps()
{
	char ch;
	while (nss.available())
	{
		ch=nss.read();
		//Serial.print(ch);
		if (gps.encode(ch)){
			//Serial.println("returns true");
			return true;
		}
	}
	return false;

}


