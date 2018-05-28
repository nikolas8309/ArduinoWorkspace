
// parameter percentage: 0-100
void setThrottle(int percentage){
  
  int throttle = map(percentage,0,100, ZERO_THROTTLE, FULL_THROTTLE);
  esc.write(throttle);
}


void setDirection(DIRECTION dir){

 switch (dir){
 case CENTER:
  pidalio.write(SERVO_CENTER);
  break;
 case LEFT:
  pidalio.write(SERVO_LEFT);
  break;
 case RIGHT:
  pidalio.write(SERVO_RIGHT);
 break;
 }
}

void setControlHolder(CONTROLHOLDER newControlHolder){
  if(newControlHolder==MICROCONTROLLER){
    digitalWrite (TO_BUFFER_PIN, LOW);
  }
  if(newControlHolder==RECEIVER){
    digitalWrite (TO_BUFFER_PIN, HIGH);
  }
}

