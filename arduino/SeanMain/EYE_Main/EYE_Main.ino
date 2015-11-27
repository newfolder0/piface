
//EYE 2015
//Sean Malikides

#include <Servo.h> 

//define pins.
#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
#define LED5 6
#define LED6 7
#define LED7 8
#define LED8 9

#define pump 11
#define valve 10

 
Servo pan;  
Servo tilt; 

//Main global variables for position and mood.

//position
int posX = 550;
int posY = 0;
int numFace = 0;
int faceSize = 0;      //what range will this be in.

//mood variables
int mood = 1;

//Intiialise Variables.
void setup() {
  

  //setup IO
  
  //LED ouput;
  for (int i = 2; i<10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i,HIGH);
  }
  
  //PUMP
  pinMode(pump, OUTPUT);
  delay(100);
  digitalWrite(pump,HIGH);
  
  //valves
  pinMode(valve, OUTPUT);
  
  //servos
  pan.attach(12);
  tilt.attach(13);
  
  
  Serial.begin(9600);
 
 delay(1000); 

}

void loop() {

  //Serial read, to get face info
  
  loopSerial();
  
  Serial.println(posX);
  
  ValveController();
  
  //Conscience();
  
  //what to do for each mood.
  //zero is sleep;
  //10 is loose shit.
//  if (mood == 0) {
//    sleeping();
//  }
//  
//  if ((mood > 0) && (mood < 10)) {
//      
//    LightControl();
//    ValveController();
//    Servo_Controller();
//    
//  }
//  
//  if (mood == 10) {
//    nervousBreakdown();
//  }
}

