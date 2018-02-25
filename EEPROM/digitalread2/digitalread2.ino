int clockread = 3;
int pinread = 2;
int data [100];//50data + 50clock
int x=2;
void setup() {
  
  Serial.begin (9600);
    pinMode (clockread,INPUT);
    pinMode (pinread,INPUT);

   //dataclock capturing
  for (int i=0,j=1;i<=100,j<=99;j=j+x,i=i+x){  
          data [i] = digitalRead( clockread);
          delay(100);
          //Serial.println (i);
            data [j] = digitalRead( pinread);
            delay (100);
            //Serial.println (j);
     }
	
	//1ος τροπος. Όλα στον ιδιο πίνακα εναλλάξ.
	for(int i=0;i<100;i+=2){
		data [i] = digitalRead( clockread);
		data [i+1] = digitalRead( pinread);
		delay(100);
	} 
	
	//2ος τρόπος. καλυτερος γιατι τα δεδομενα πανε σε διαφορετικους πινακες.
	int data1[50];
	int data2[50];
	for(int i=0;i<50;i++){
		data1 [i] = digitalRead( clockread);
		data2 [i] = digitalRead( pinread);
		delay(100);
	}
	
    for (int i=0,j=1;i<=100,j<=99;j=j+x,i=i+x)
      Serial.print (data[i]);
      Serial.print ("-");
      Serial.println (data[j]);
  
 

void loop() {
  // put your main code here, to run repeatedly:

}
