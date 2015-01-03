int rechterSpeedVooruit = 0;
int rechterSpeedAchter=0;
int linkerSpeedVooruit = 0;
int linkerSpeedAchter=0;
String incomingText;
int incomingByte;
double calc=0;

void setup()
{
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}
void loop()
{
    calc=0;
    if (Serial.available()) { 
      // if the data came
      incomingByte=Serial.parseInt();
        
      // straight
      if (incomingByte >-15 && incomingByte < 15) {
          rechterSpeedVooruit = 210;
          linkerSpeedVooruit = 200;
          linkerSpeedAchter=0;
          rechterSpeedAchter=0;
          Rijden();
      }
      // right
      else if (incomingByte > 16 && incomingByte < 40) {
          rechterSpeedVooruit = 210;
          linkerSpeedVooruit = 175;
          linkerSpeedAchter=0;
          rechterSpeedAchter=0;
          Rijden();
      }
      // left
      else if (incomingByte < -16 && incomingByte > -40) {
          rechterSpeedVooruit = 175;
          linkerSpeedVooruit = 200;
          linkerSpeedAchter=0;
          rechterSpeedAchter=0;
          Rijden();
      }
      else if (incomingByte > 41 && incomingByte < 70) {
          rechterSpeedVooruit = 210;
          linkerSpeedVooruit = 150;
          linkerSpeedAchter=0;
          rechterSpeedAchter=0;
          Rijden();
      }
      // left
      else if (incomingByte < -41 && incomingByte > -70) {
          rechterSpeedVooruit = 150;
          linkerSpeedVooruit = 200;
          linkerSpeedAchter=0;
          rechterSpeedAchter=0;
          Rijden();
      }
      // stop      
      else if (incomingByte == 200) {
        LeggedStille();
      }
      
      Serial.println(Serial.read());  // print message
      Serial.println(incomingByte);
      Serial.println(incomingText);
      Serial.write("1");
      Rijden();
   }
}

void LeggedStille()
{ 


  rechterSpeedVooruit=0;
  linkerSpeedVooruit=0;
  linkerSpeedAchter=0;
  rechterSpeedAchter=0;  
  analogWrite(5,0);
  analogWrite(6,0);
  analogWrite(10,0);
  analogWrite(11,0);
  
}

void Rijden()
{
  //vooruit rechterwiel
  // 5 HIGH 6 LOW
  analogWrite(5,rechterSpeedAchter);
  analogWrite(6,rechterSpeedVooruit);
  //delay(1000);

  //vooruit linkerwiel
  // 10 HIGH 11 LOW
  analogWrite(10,linkerSpeedVooruit);
  analogWrite(11,rechterSpeedAchter);
  //delay(1000);
}
