void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    delay(1000);
    int a=5;
    int b=8;
    int c=2;
    int d=6;
    
    int res1 = getMax(a,b);
    Serial.println(res1);
    
    int res2 = getMax(c,d);
    Serial.println(res2);
}

int getMax(int num1,int num2){
  int maxNum;
  if(num1>=num2){
    maxNum=num1;
  }
  else{
    maxNum=num2;
  }
  return maxNum;
}

void loop(){}

