

//lighting constants 
int left2 = 0;
int left1 = 160;
int center = 320;
int right1 = 480;
int right2 = 640;

void LightControl() {
  
  //lighting responds with cam pos and mood.
  
  //calculate distance.
  //not sure if this is the right way around.
  int distleft2 = (left2 - posX)<0?-1*(left2 - posX):(left2 - posX);
  int distleft1 = (left1 - posX)<0?-1*(left1 - posX):(left1 - posX);
  int distcenter = (center - posX)<0?-1*(center - posX):(center - posX); 
  int distright1 = (right1 - posX)<0?-1*(right1 - posX):(right1 - posX);
  int distright2 = (right2 - posX)<0?-1*(right2 - posX):(right2 - posX);
  
  //normalise
  float intensityleft2 = ((float)distleft2/640)*255;
  float intensityleft1 = ((float)distleft1/640)*255;
  float intensitycenter = ((float)distcenter/640)*255;;
  float intensityright1 = ((float)distright1/640)*255;
  float intensityright2 = ((float)distright2/640)*255;

  //pair correct lights together
  analogWrite(LED1, (int)intensityleft2);
  
  //>>>>>>>>>>>>>>>>>>>>>>>>
  analogWrite(LED2, (int)intensityleft1);
  analogWrite(LED3, (int)intensityleft1);
  
  //>>>>>>>>>>>>>>>>>>>>>>>>
  analogWrite(LED4, (int)intensitycenter);
  analogWrite(LED5, (int)intensitycenter);

  //>>>>>>>>>>>>>>>>>>>>>>>>
  analogWrite(LED6, (int)intensityright1);
  analogWrite(LED7, (int)intensityright1);

  //>>>>>>>>>>>>>>>>>>>>>>>>
  analogWrite(LED8, (int)intensityright2);

  

}
