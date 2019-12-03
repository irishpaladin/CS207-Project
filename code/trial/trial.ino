/*
 Morse Code

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

int uTime=240;

const byte ledb[10] = {

  B00000000 ,B10000000,B01011011,B01001111,B01100110,B01101101,B01111101,B00000111,B01111111,B01101111
};

int data = 2; 
int clock = 3;
int latch = 4;

int anode2 = 10;
int anode1 = 9;

int anodepins[]={8,9,10,11};

int b1[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int b2[] = {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0};
int b3[] = {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0};
int b4[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t bit1 = 0;
uint32_t bit2 = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(anode1, OUTPUT);
  pinMode(anode2,OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);  
  pinMode(latch, OUTPUT);  
  bit1 += (ledb[0] << 0);
bit1 += (ledb[1] << 8);
bit2 += (ledb[1] << 0);
bit2 += (ledb[0] << 8);
}

// the loop function runs over and over again forever
void loop() {
  /*
  digitalWrite(latch, LOW);     //Pulls the chips latch low
  shiftOut(data, clock, MSBFIRST, 1); //Shifts out the 8 bits to the shift register
  digitalWrite(latch, HIGH);   //Pulls the latch high displaying the data
  digitalWrite(anode1, LOW);
  digitalWrite(anode2,HIGH);
  delay(500);

  digitalWrite(latch, LOW);     //Pulls the chips latch low
  shiftOut(data, clock, MSBFIRST, 0); //Shifts out the 8 bits to the shift register
  digitalWrite(latch, HIGH);   //Pulls the latch high displaying the data
  digitalWrite(anode1, HIGH);
  digitalWrite(anode2,LOW);
  delay(500);
*/
int cathode_p[]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int anode_p[]={1,0,0,0};
updateLED2(cathode_p,anode_p);
delay(500);

anode_p[0]=0;
anode_p[1]=1;
updateLED2(cathode_p,anode_p);
delay(500);

anode_p[1]=0;
anode_p[2]=1;
updateLED2(cathode_p,anode_p);
delay(500);

anode_p[2]=0;
anode_p[3]=1;
updateLED2(cathode_p,anode_p);
delay(500);


/*
  updateLED(b1, 1, 0);
  delay(500);

  updateLED(b2, 0, 1);
  delay(500);

  updateLED(b4, 0, 0);
  delay(500);

  updateLED(b3, 1, 1);
  delay(500);
*/
  
 
  
}

void updateLED2(int cathode[], int anodestate[]){
  digitalWrite(latch, LOW);     //Pulls the chips latch low
  //shiftOut(data, clock, MSBFIRST, B10000000 ); //Shifts out the 8 bits to the shift register
  
  for(int i=0;i<16;i++){
    //digitalWrite(data, LOW);
    
    if(cathode[i]==1){digitalWrite(data, HIGH);} //if bit 8 is a 1, set our data pin high
    else{digitalWrite(data, LOW);}            //if bit 8 is a 0, set the data pin low
    digitalWrite(clock, HIGH);                //the next three lines pulse the clock
    delay(1);
    digitalWrite(clock, LOW);
  }
  digitalWrite(latch, HIGH);   //Pulls the latch high displaying the data

  for(int i=0;i<4;i++){
    digitalWrite(anodepins[i],anodestate[i]);
  }
  //digitalWrite(anode1, a1);
  //digitalWrite(anode2,a2);
}

void updateLED(int pattern[], int a1, int a2){
  digitalWrite(latch, LOW);     //Pulls the chips latch low
  //shiftOut(data, clock, MSBFIRST, B10000000 ); //Shifts out the 8 bits to the shift register
  
  for(int i=0;i<16;i++){
    //digitalWrite(data, LOW);
    
    if(pattern[i]==1){digitalWrite(data, LOW);} //if bit 8 is a 1, set our data pin high
    else{digitalWrite(data, HIGH);}            //if bit 8 is a 0, set the data pin low
    digitalWrite(clock, HIGH);                //the next three lines pulse the clock
    delay(1);
    digitalWrite(clock, LOW);
  }
  digitalWrite(latch, HIGH);   //Pulls the latch high displaying the data
  
  digitalWrite(anode1, a1);
  digitalWrite(anode2,a2);
}
