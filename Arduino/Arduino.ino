int rechterSpeedVooruit = 0;
int rechterSpeedAchter=0;
int linkerSpeedVooruit = 0;
int linkerSpeedAchter=0;
char incomingText;
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
        incomingText = Serial.read(); // read byte
        incomingByte=incomingText-'0';
        if(incomingText=='0')
        {
          rechterSpeedVooruit=0;
          linkerSpeedVooruit=0;
          linkerSpeedAchter=0;
          rechterSpeedAchter=0;
          Rijden();
        }
        if(incomingByte==2){
          rechterSpeedVooruit=255;
          linkerSpeedVooruit=255;
          linkerSpeedAchter=0;
          rechterSpeedAchter=0;
          Rijden();
        }
        if(incomingByte==3){
          rechterSpeedVooruit=0;
          linkerSpeedVooruit=0;
          linkerSpeedAchter=255;
          rechterSpeedAchter=255;
          Rijden();
        }
        if(incomingByte>10)
        {
            calc = (calc/10)*25.5;
            rechterSpeedVooruit=calc;
            linkerSpeedVooruit=255;
            linkerSpeedAchter=0;
            rechterSpeedAchter=0;
            
        }  
        if(incomingByte<-10)
        {
            calc = -((calc/10)*25.5);
            rechterSpeedVooruit=calc;
            linkerSpeedVooruit=255;
            linkerSpeedAchter=0;
            rechterSpeedAchter=0;       
        }  
        if(incomingByte=='-200')
        {
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
