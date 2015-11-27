//need to schedule valve timing

long onTime = 100;           //scheduled on time.
long offTime = 500;          //scheduled off time.
int bubblePeriod;      //milliseconds.

int bubbleFactor = 100;
int bubbleConstant = 1000; 

int valveOpen = 1;

void ValveController() {
  
  bubblePeriod = 1000;//bubbleFactor*(10 - mood) + bubbleConstant;
   
  if ((valveOpen == 1) && (millis() > onTime)) {
    //turn valve on;
    digitalWrite(11, HIGH);
    
    //set off time;
    offTime = millis() + bubblePeriod + random(0,1000);
    valveOpen = 0;
    //Serial.println("on");
    
  } 
  if ((valveOpen == 0) && (millis() > offTime)) {
    //turn valve off;
    digitalWrite(11, LOW);
    
    //set off time;
    onTime = millis() + bubblePeriod + random(0,1000);
    valveOpen  = 1;
    //Serial.println("off");
  } 
  
  
}
