
// parameter percentage: 0-100
void setThrottle(int percentage){
  
  int throttle = map(percentage,0,100, ZERO_THROTTLE, FULL_THROTTLE);
  esc.write(throttle);
}


void setDirection(DIRECTION dir){

 switch (dir){
 case CENTER:
  myservo.write(SERVO_CENTER);
  break;
 case LEFT:
  myservo.write(SERVO_LEFT);
  break;
 case RIGHT:
  myservo.write(SERVO_RIGHT);
 break;
 }
}

void setControlHolder(CONTROLHOLDER newControlHolder){
  if(newControlHolder==ARDUINO){
    digitalWrite (TO_BUFFER_PIN, HIGH);
  }
  if(newControlHolder==RECEIVER){
    digitalWrite (TO_BUFFER_PIN, LOW);
  }
}

