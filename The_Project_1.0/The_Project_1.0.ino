//The Electromagnet Setting
////////////////////////////////////
int magnet = 30;
int ground = 32;
////////////////////////////////////
//Robot Arm Setting
///////////////////////////////////////
float theta1 = 0;float theta2 = 0;float theta3 = 0;
int cp1 = 2;int dir1 =3;int opto1 = 4;
int cp2 = 5;int dir2 =6;int opto2 = 7;
int cp3 = 8;int dir3 =9;int opto3 = 10;
int stepdelay = 100; int stop1 = 10*10/1.8;
////////////////////////////////////
//Communication Setting
////////////////////////////////////////
float get_theta[3];
//////////////////////////
/////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(cp1,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(opto1,OUTPUT);
  pinMode(cp2,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(opto2,OUTPUT);
  pinMode(cp3,OUTPUT);
  pinMode(dir3,OUTPUT);
  pinMode(opto3,OUTPUT);
  pinMode(magnet,OUTPUT);
  pinMode(ground,OUTPUT);
  digitalWrite(magnet,HIGH);
  digitalWrite(ground,HIGH);
  digitalWrite(ground,LOW);
  digitalWrite(opto1,HIGH);
  digitalWrite(opto2,HIGH);
  digitalWrite(opto3,HIGH);
}

void loop() 
{
  //////Get the theta////
  //////////////////////
  communication();
  theta1=get_theta[1];
  theta2=get_theta[2];
  theta3=get_theta[3];
  //////////////////////
  //Serial.println("Start Working");
  stepper1(theta1);
  stepper3(theta3);
  stepper2(theta2);

 // magnet_run();
   delay(100);
  digitalWrite(magnet,HIGH);
  digitalWrite(ground,HIGH);
   delay(20);
   digitalWrite(ground,LOW);
  delay(500);
  //Serial.println("Back To Origin");
  stepback2(theta2);
  stepback3(theta3);delay(100);
  stepback1(theta1);delay(100);
  stepper1(90);
  stepper2(50);
 // magnet_stop();
   delay(100);
  digitalWrite(magnet,HIGH);
  digitalWrite(ground,HIGH);
   delay(20);
   digitalWrite(ground,LOW);
   delay(300);
   stepback2(50);
   stepback1(90-2);
   delay(500);
  //Serial.println("Work Done");
  
}

void magnet_run()
{
  delay(500);
  digitalWrite(magnet,HIGH);
  digitalWrite(ground,HIGH);
   delay(20);
   digitalWrite(ground,LOW);
   
}

void magnet_stop()
{
  delay(500);
  digitalWrite(magnet,HIGH);
  digitalWrite(ground,HIGH);
   delay(20);
   digitalWrite(ground,LOW);
  
}

void communication()
{
  int flag = 0;
   while(flag == 0)
  {
    delay(50);
    if(Serial.available() >= 3)
   {
      for(int i=1;i<=3;i++)
     {
       get_theta[i] = Serial.parseFloat();
       delay(50);
       Serial.println(get_theta[i]);
       delay(50);
     }
     flag = 1;
   }   
  }
  
}

void wait_data()
{
  delay(50);
}

void stepper1(float theta)
{
  int w=theta*stop1;
  if (theta >= 0)
  {
    digitalWrite(dir1,HIGH);
  }
  else 
  {
    digitalWrite(dir1,LOW);
    w = -(theta*stop1);
  }
  for(int i = 0;i < w;i++)
  {
    digitalWrite(cp1,HIGH);
    delayMicroseconds(stepdelay);
    digitalWrite(cp1,LOW);
    delayMicroseconds(stepdelay);
  }
}

void stepper2(float theta)
{
  int w=theta*stop1;
  if (theta >= 0)
  {
    digitalWrite(dir2,HIGH);
  }
  else 
  {
    digitalWrite(dir2,LOW);
    w = -(theta*stop1);
  }
  for(int i = 0;i < w;i++)
  {
    digitalWrite(cp2,HIGH);
    delayMicroseconds(stepdelay);
    digitalWrite(cp2,LOW);
    delayMicroseconds(stepdelay);
  }
}

void stepper3(float theta)
{
  int w=theta*stop1;
  if (theta >= 0)
  {
    digitalWrite(dir3,HIGH);
  }
  else 
  {
    digitalWrite(dir3,LOW);
    w = -(theta*stop1);
  }
  for(int i = 0;i < w;i++)
  {
    digitalWrite(cp3,HIGH);
    delayMicroseconds(stepdelay);
    digitalWrite(cp3,LOW);
    delayMicroseconds(stepdelay);
  }
}


void stepback1(float theta)
{
  int w=theta*stop1;
  if (theta >= 0)
  {
    digitalWrite(dir1,LOW);
  }
  else 
  {
    digitalWrite(dir1,HIGH);
    w = -(theta*stop1);
  }
  for(int i = 0;i < w;i++)
  {
    digitalWrite(cp1,HIGH);
    delayMicroseconds(stepdelay);
    digitalWrite(cp1,LOW);
    delayMicroseconds(stepdelay);
  }
}

void stepback2(float theta)
{
  int w=theta*stop1;
  if (theta >= 0)
  {
    digitalWrite(dir2,LOW);
  }
  else 
  {
    digitalWrite(dir2,HIGH);
    w = -(theta*stop1);
  }
  for(int i = 0;i < w;i++)
  {
    digitalWrite(cp2,HIGH);
    delayMicroseconds(stepdelay);
    digitalWrite(cp2,LOW);
    delayMicroseconds(stepdelay);
  }
}

void stepback3(float theta)
{
  int w=theta*stop1;
  if (theta >= 0)
  {
    digitalWrite(dir3,LOW);
  }
  else 
  {
    digitalWrite(dir3,HIGH);
    w = -(theta*stop1);
  }
  for(int i = 0;i < w;i++)
  {
    digitalWrite(cp3,HIGH);
    delayMicroseconds(stepdelay);
    digitalWrite(cp3,LOW);
    delayMicroseconds(stepdelay);
  }
}
