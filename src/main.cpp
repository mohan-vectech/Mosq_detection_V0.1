#include <Arduino.h>

#define laser1 4
#define sensor1 5
#define laser2 6
#define sensor2 7

#define BUFFER_TIME 500

int detectionFlag1;
int detectionFlag2;
long timeWhenDetected;
bool resetFlag;
int count;


void setup()
{
  Serial.begin(115200);
  pinMode(laser1, OUTPUT);
  pinMode(sensor1, INPUT);
  pinMode(laser2, OUTPUT);
  pinMode(sensor2, INPUT);

  digitalWrite(laser1, HIGH);
  digitalWrite(laser2, HIGH);
  resetFlag = true;
  count = 0;
}

void loop()
{
  detectionFlag1 = digitalRead(sensor1);
  detectionFlag2 = digitalRead(sensor2);


  if ((detectionFlag1 == HIGH) || (detectionFlag2 == HIGH)) //testing git comment
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
