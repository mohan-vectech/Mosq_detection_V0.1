#include <Arduino.h>

#define laser 4
#define sensor 5

#define BUFFER_TIME 500

int detectionFlag;
long timeWhenDetected;
bool resetFlag;
int count;



void setup()
{
  Serial.begin(115200);
  pinMode(laser, OUTPUT);
  pinMode(sensor, INPUT);

  digitalWrite(laser, HIGH);
  resetFlag = true;
  count = 0;
}

void loop()
{
  detectionFlag = digitalRead(sensor);

  if (detectionFlag == HIGH) //testing git comment
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
