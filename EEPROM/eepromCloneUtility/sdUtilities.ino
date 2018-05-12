bool sdCardInit=false;

bool initSd()
{
  if(sdCardInit)return true;

  
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  //pinMode(10, OUTPUT);
  //pinMode(9, OUTPUT);

  if (!SD.begin(4)) 
  {
    Serial.println(F("SD initialization failed!"));
    return false;
  }
  Serial.println(F("SD initialization done."));
  sdCardInit=true;
  return true;
}

//---------------------------------------------

bool openFileForRead(){
  myFile = SD.open("image.txt");

  if(myFile)
  {
    Serial.println(F("successfully opened image.txt"));
    
    return true;
  }
  else
  {
    Serial.println(F("error opening image.txt"));
    return false;
  } 
}

//---------------------------------------------

bool openFileForWrite(){


    if(SD.exists("dump.txt") ){
    SD.remove("dump.txt");
    Serial.println("existing file removed.");
  }

    myFile = SD.open("dump.txt", FILE_WRITE);

  if(myFile)
  {
    Serial.println(F("successfully opened dump.txt"));
    return true;
  }
  else
  {
    Serial.println(F("error opening dump.txt"));
    return false;
  } 
}

//------------------------------------------

bool closeFile(){
    myFile.close();
    return true;
}


