int setWaypointPin = 5;


void setup() {
  // put your setup code here, to run once:
  pinMode(setWaypointPin , INPUT);
  Serial.begin (115200);
}

void loop() {
    
  if( checkSetWaypointButton()){//to koumpi exei patithei
    Serial.println("koumpi patithike ");
  }    
  delay(50);
}
/**
 * epistrefei true sthn metavash apo low se high
 * epistrefei false sthn metavash apo high se low
 */
bool checkSetWaypointButton ()
{
  bool buttonState;
  static bool previousState = false;
  
  buttonState = digitalRead(setWaypointPin);
//  Serial.print("buttonState=");
//  Serial.print(buttonState);
//  Serial.print("  previousState=");
//  Serial.println(previousState);
  
  if(buttonState==HIGH && previousState==LOW){//patima
    previousState=buttonState;
    return true;
  }
  
  else{ //se kathe alli periptosi
    previousState=buttonState;
    return false;
  }
}
