#include <Wire.h>
#include <Adafruit_VEML7700.h>

Adafruit_VEML7700 veml = Adafruit_VEML7700();
byte RedLED = 1; 
byte BluLED = 2;
byte GrnLED = 42;  
int  RedFade = 100;
int  BluFade = 100;
int  GrnFade = 100;
int count;

int enA = 0;
int in1 = 45;
int in2 = 48;

float sumCount = 0;
float dynThreshold = 0;
int calibCount = 1;
unsigned long starttime = 0;
unsigned long endtime = 0;

float currentRead = 0;
float lastRead = 0;
float diffBetweenReads;

void setup() {
  pinMode(RedLED, OUTPUT);  
  pinMode(BluLED, OUTPUT);
  pinMode(GrnLED, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(enA, HIGH);

  count = 0;

  Serial.begin(9600);
  Wire.begin(8, 9);  // (SDA, SCL)
  while (!Serial) delay(10);  // wait for Serial to be ready
  Serial.println("Adafruit VEML7700 Test");


  if (!veml.begin()) {
    Serial.println("Failed to communicate with VEML7700 sensor, check wiring?");
    while (1);
  }
  Serial.println("Found VEML7700 sensor");

  // Set sensor settings if needed
  veml.setGain(VEML7700_GAIN_1);
  veml.setIntegrationTime(VEML7700_IT_100MS);

  Serial.print(F("Gain: "));
  Serial.println(veml.getGain());
  Serial.print(F("Integration Time: "));
  Serial.println(veml.getIntegrationTime());

  // begin callibration
  

  //Serial.println("start reading is:");
  //Serial.println(veml.readLux());

  analogWrite(RedLED,RedFade);
  analogWrite(BluLED,BluFade);
  analogWrite(GrnLED,GrnFade);

  starttime = millis();
  endtime = starttime;
  Serial.println("Beginning calibration (10 sec)");

  
}

void loop() {
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  while ((endtime - starttime) <=10000)
  {
     sumCount = veml.readLux() + sumCount;
     endtime = millis();   
     calibCount++;
  } 
  
dynThreshold = sumCount/calibCount;
currentRead = veml.readLux();

if (((dynThreshold  - currentRead) > 1) && diffBetweenReads < -0.1) {
      //Serial.print("Lux at count: ");
      Serial.println(veml.readLux());
      Serial.print("Count: ");
      count++;
      Serial.println(count);
      //delay(100); 
}

 lastRead = veml.readLux();
 diffBetweenReads = (currentRead - lastRead);

 //Serial.println("current - last =");
 //Serial.println(diffBetweenReads);

 //else {
  //Serial.print("Unblocked lux: ");
  //Serial.println(veml.readLux());
 //}
}
