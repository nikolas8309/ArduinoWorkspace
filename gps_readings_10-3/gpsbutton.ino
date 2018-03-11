

void gpsbutton ()
{

 
  if (buttonstate == HIGH)
  
          //diavase tis sintetagmenes apo to gps kai valtes
          //sthn RAM san flat2 kai flon2
          flat = flat2;
          flon = flon2;
          Serial.println (flat2);
          Serial.println (flon2);
          
  
}
