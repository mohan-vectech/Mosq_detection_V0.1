#include <Arduino.h>

//#define laser1 4
//#define laser2 6
//#define laser3 4
//#define laser4 6
//#define laser5 4

#define sensor1 11
#define sensor2 10
#define sensor3 9
#define sensor4 46
#define sensor5 3
 
#define BUFFER_TIME 250

int detectionFlag1;
int detectionFlag2;
int detectionFlag3;
int detectionFlag4;
int detectionFlag5;

long timeWhenDetected;
bool resetFlag;
int count;


void setup()
{
  Serial.begin(9600);
  //pinMode(laser1, OUTPUT);
  //pinMode(laser2, OUTPUT);

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);

  //digitalWrite(laser1, HIGH);
  //digitalWrite(laser2, HIGH);
  resetFlag = true;
  count = 0;
}

void loop()
{
  detectionFlag1 = digitalRead(sensor1);
  detectionFlag2 = digitalRead(sensor2);
  detectionFlag3 = digitalRead(sensor3);
  detectionFlag4 = digitalRead(sensor4);
  detectionFlag5 = digitalRead(sensor5);


  if ((detectionFlag1 == HIGH) || (detectionFlag2 == HIGH) || (detectionFlag3 == HIGH) || (detectionFlag4 == HIGH) || (detectionFlag5 == HIGH)) //testing git comment
  {
    

    // Serial.print("outside inner loop");
    // Serial.println(detectionFlag);
    if (resetFlag && (millis() - timeWhenDetected >= BUFFER_TIME))
    {

      Serial.print("Mosquito Detected: ");
      count++;
      Serial.println(count);
      // Serial.println(detectionFlag);
      resetFlag = false;
    }
    timeWhenDetected = millis();
  }
  else
  {
    resetFlag = true;
  }
}
