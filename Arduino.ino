#include <SoftwareSerial.h>
#include <NewPing.h>
 
#define TRIGGER_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 500
 
 
NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE);
SoftwareSerial mySerial(0, 1);
int rechterSpeedVooruit = 0;
int rechterSpeedAchter=0;
int linkerSpeedVooruit = 0;
int linkerSpeedAchter=0;
int distanceCm;
char incomingByte;
boolean hasCollided=false;
void setup()
{
  Serial.begin(9600);
  pinMode(13,INPUT);
  pinMode(12,INPUT);
  digitalWrite(13,HIGH);
  digitalWrite(12,HIGH);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
 
  pinMode(A0,OUTPUT);
  pinMode(A1,INPUT);
 
}
void loop()
{
  botsDetectie();
  //Serial.print("sensor = "+analogRead(0));
  //Serial.print(analogRead(2));
 
 if (Serial.available() > 0) {  // if the data came
    incomingInt = Serial.parseInt(); // Parse Int
    if(incomingInt>-10 & incomingInt < 10 && hasCollided==false)
    {
      rechterSpeedVooruit=255;
      linkerSpeedVooruit=250;
      linkerSpeedAchter=0;
      rechterSpeedAchter=0;
      Rijden();
    } 
    else if(incomingInt>10)
    {
      rechterSpeedVooruit=255-incomingInt;
      linkerSpeedVooruit=250;
      linkerSpeedAchter=0;
      rechterSpeedAchter=0;
      Rijden();
    }
    else if(incomingInt<-10)
    {
      rechterSpeedVooruit=255;
      linkerSpeedVooruit=255-incomingInt*-1;
      linkerSpeedAchter=0;
      rechterSpeedAchter=0;
      Rijden();
    }
    if(incomingInt=='5')
    {
      LeggedStille();
    }
    Serial.println(Serial.read());  // print message
 }
}
void botsDetectie()
{
  delay(100);
  distanceCm = sonar.ping_cm();
  Serial.print(distanceCm);
  if(distanceCm<15 && distanceCm>0)
  {
    if(hasCollided==false)
    {
        LeggedStille();
    }
    hasCollided=true;
 
  }
  else
  {
    hasCollided=false;
  }
}
void LeggedStille()
{        
  analogWrite(5,0);
  analogWrite(6,0);
  analogWrite(10,0);
  analogWrite(11,0);
 
}
 
void Rijden()
{
  //vooruit rechterwiel
  // 5 HIGH 6 LOW
  analogWrite(5,rechterSpeedVooruit);
  analogWrite(6,rechterSpeedAchter);
  //delay(1000);
 
  //vooruit linkerwiel
  // 10 HIGH 11 LOW
  analogWrite(10,linkerSpeedVooruit);
  analogWrite(11,rechterSpeedAchter);
  //delay(1000);
}
