#include <EEPROM.h>

// Shift register pins
const int data = 2; 
const int clock = 3;
const int latch = 4;

// Anode pins
const int anodepins[]={6,9,10,11};

// Button pins
const int rbutton = 12;
const int bbutton = 13;

// Initialize the state of anodes and cathodes
int cathode_p[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int anode_p[] = {0,0,0,0};

int mode = 0; // either turned on or off
#define TURNED_OFF 0
#define TURNED_ON 1

int pattern = 0; // current pattern playing
int maxPattern = 8; //the max number of pattern

// types of pattern
#define EVERYTHING 1
#define EVERYTHING_ON 2
#define DIMMER 3
#define ONE_H_LAYER 4
#define ONE_V_LAYER 5
#define ALTERNATE_V 6
#define ALTERNATE_H 7
#define ALTERNATE_LEDS 8



void setup() {
  // Initialize the shift register's output pins
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);  
  pinMode(latch, OUTPUT);  

  // Configures buttons for internal pullup
  pinMode(rbutton, INPUT);
  pinMode(bbutton, INPUT);
  digitalWrite(rbutton, HIGH); 
  digitalWrite(bbutton, HIGH);
  
  // Initialize the anodepins as output
  for(int i=0;i<4;i++){
    pinMode(anodepins[i],OUTPUT);
  }

  // Load the pattern previously
  EEPROM.get(0,pattern);
  // initial mode
  mode = TURNED_ON;
}

// the loop function
void loop() {
  
  // Red button is clicked, mode is off
  if(!(digitalRead(rbutton))){
    while(!(digitalRead(rbutton)));
    EEPROM.put(0,pattern);
    mode = TURNED_OFF;
  }
  // Black button is clicked, change pattern
  if(!(digitalRead(bbutton))){
    while(!(digitalRead(bbutton)));
    if(pattern == maxPattern){pattern = 1;}
    else pattern++;
    EEPROM.put(0,pattern);
  }
  // TURNED_OFF mode
  if(mode == TURNED_OFF){
    showPattern0();
    while(digitalRead(rbutton)); // Everything off until red button is LOW(clicked)
    while(!digitalRead(rbutton)); //Turns on again if clicked
    EEPROM.get(0,pattern);
    mode = TURNED_ON;
  }
  //TURNED_ON mode
  else{
    switch(pattern){
      //checks if button off is is clicked every end of pattern
      case EVERYTHING:
        showPattern1();
        if(isOff()){break;}
        showPattern2();
        if(isOff()){break;}
        showPattern3();
        if(isOff()){break;}
        showPattern4();
        if(isOff()){break;}
        showPattern5();
        if(isOff()){break;}
        break;
      case EVERYTHING_ON:
        showPattern1();
        break;
      case DIMMER:
        showPattern2();
        break;
      case ONE_H_LAYER:
        showPattern3();
        break;
      case ONE_V_LAYER:
        showPattern4();
        break;
      case ALTERNATE_H:
        showPattern5();
        break;
      case ALTERNATE_V:
        showPattern6();
        break;
      case ALTERNATE_LEDS:
        showPattern7();
        break;  
      default:
        break;
    }
  }
 
  
}


// Everything turned off
void showPattern0(){
  setCathodes(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  setAnodes(0,0,0,0);
  updateLED();
  delay(500);
}


// Everything turned on
void showPattern1(){
  setCathodes(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  setAnodes(1,1,1,1);
  updateLED();
  delay(500);
}


// Dimming lights
void showPattern2(){
  int cathode_p2[]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  // Update cathodes
  digitalWrite(latch, LOW);     //Pulls the chips latch low
  for(int i=0;i<16;i++){    
    if(cathode_p2[i]==1){digitalWrite(data, HIGH);} //if bit 8 is a 1, set our data pin high
    else{digitalWrite(data, LOW);}            //if bit 8 is a 0, set the data pin low
    digitalWrite(clock, HIGH);                //the next three lines pulse the clock
    delay(1);
    digitalWrite(clock, LOW);
  }
  digitalWrite(latch, HIGH);   //Pulls the latch high displaying the data
  
  // Update anodes
  for(int i=0;i<=5;i++){
    for(int j =0;j<4; j++){
      analogWrite(anodepins[j],i*50);
    }
    delay(200);
  }
  for(int i=4;i>=1;i--){
    for(int j =0;j<4; j++){
      analogWrite(anodepins[j],i*50);
    }
    delay(200);
  }
}


// Lights up one layer at a time
void showPattern3(){
  setCathodes(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  setAnodes(1,0,0,0);
  updateLED();
  delay(500);
  
  anode_p[0]=0;
  anode_p[1]=1;
  updateLED();
  delay(500);
  
  anode_p[1]=0;
  anode_p[2]=1;
  updateLED();
  delay(500);
  
  anode_p[2]=0;
  anode_p[3]=1;
  updateLED();
  delay(500);
}


// Lights up one vertical layer at a time
void showPattern4(){
  setCathodes(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
  setAnodes(1,1,1,1);
  for(int i =0; i<4;i++){
    cathode_p[i*4]=0;
    cathode_p[i*4+1]=0;
    cathode_p[i*4+2]=0;
    cathode_p[i*4+3]=0;
    updateLED();
    delay(500);
    cathode_p[i*4]=1;
    cathode_p[i*4+1]=1;
    cathode_p[i*4+2]=1;
    cathode_p[i*4+3]=1;
  }  
}

// Alternate vertical layer one and off
void showPattern5(){
  setAnodes(1,1,1,1);
  setCathodes(1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0);
  updateLED();
  delay(500); 
  setCathodes(0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1);
  updateLED();
  delay(500); 
  setCathodes(1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0);
  updateLED();
  delay(500); 
  setCathodes(0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1);
  updateLED();
  delay(500); 
}

// Alternate horizontal layer one and off
void showPattern6(){
  setCathodes(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  setAnodes(1,0,1,0);
  updateLED();
  delay(500); 
  setAnodes(0,1,0,1);
  updateLED();
  delay(500); 
  setAnodes(1,0,1,0);
  updateLED();
  delay(500); 
  setAnodes(0,1,0,1);
  updateLED();
  delay(500); 
}

// Alternate LED
void showPattern7(){
  setAnodes(1,1,1,1);
  setCathodes(1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1);
  updateLED();
  delay(500); 
  setCathodes(0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0);
  updateLED();
  delay(500); 
  setCathodes(1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1);
  updateLED();
  delay(500); 
  setCathodes(0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0);
  updateLED();
  delay(500); 
}

// Sets the pattern in the LEDs
void updateLED(){
  // Update cathodes
  digitalWrite(latch, LOW);     //Pulls the chips latch low
  for(int i=0;i<16;i++){
    if(cathode_p[i] == 1){digitalWrite(data, HIGH);} //if bit 8 is a 1, set our data pin high
    else{digitalWrite(data, LOW);}            //if bit 8 is a 0, set the data pin low
    digitalWrite(clock, HIGH);                //the next three lines pulse the clock
    delay(1);
    digitalWrite(clock, LOW);
  }
  digitalWrite(latch, HIGH);   //Pulls the latch high displaying the data

  // Update anodes
  for(int i=0;i<4;i++){
    digitalWrite(anodepins[i], anode_p[i]);
  }
}

// Set the states of cathode pins
void setCathodes(int c0, int c1, int c2, int c3, int c4, int c5, int c6, int c7, 
                int c8, int c9, int c10, int c11, int c12, int c13, int c14, int c15){
   cathode_p[0]=c0;
   cathode_p[1]=c1; 
   cathode_p[2]=c2; 
   cathode_p[3]=c3; 
   cathode_p[4]=c4; 
   cathode_p[5]=c5; 
   cathode_p[6]=c6; 
   cathode_p[7]=c7; 
   cathode_p[8]=c8; 
   cathode_p[9]=c9; 
   cathode_p[10]=c10; 
   cathode_p[11]=c11; 
   cathode_p[12]=c12; 
   cathode_p[13]=c13; 
   cathode_p[14]=c14; 
   cathode_p[15]=c15;                               
}

// Sets the state of the anode pins
void setAnodes(int a0, int a1, int a2, int a3){
  anode_p[0] = a0;
  anode_p[1] = a1;
  anode_p[2] = a2;
  anode_p[3] = a3;
}

//checks if red button is clicked
bool isOff(){
  if(!(digitalRead(rbutton))){
    while(!(digitalRead(rbutton)));
    EEPROM.put(0,pattern);
    mode = TURNED_OFF;
    return true;
  }
  return false;
}
