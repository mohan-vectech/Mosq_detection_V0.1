#include <Wire.h>
#include <Adafruit_VEML7700.h>

Adafruit_VEML7700 veml = Adafruit_VEML7700();

int count;

int enA = 0;
int in1 = 45;
int in2 = 48;

float sumCount = 0;
float dynThreshold = 0;
int calibCount = 0;
unsigned long starttime = 0;

float currentRead = 0;
float lastRead = 0;
float diffBetweenReads;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(enA, HIGH);

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
  veml.setIntegrationTime(VEML7700_IT_200MS);

  Serial.print(F("Gain: "));
  Serial.println(veml.getGain());
  Serial.print(F("Integration Time: "));
  Serial.println(veml.getIntegrationTime());

  // begin calibration
  
  starttime = millis();
  Serial.println("Beginning calibration period (30 sec)");
  int lastDisplayedTime = 30; // Timer starts from 30 seconds


  while ((millis() - starttime) <= 30000) { // Run for 30 seconds
    float lux = veml.readLux(); // Read sensor once per loop iteration
    sumCount += lux;            // Add to total sum
    calibCount++;               // Increment reading count
    //delay(50);                  // Add a slight delay to avoid excessive reads
    int timeElapsed = (millis() - starttime) / 1000; // Elapsed time in seconds
    int timeRemaining = 30 - timeElapsed;

    if (timeRemaining != lastDisplayedTime) { // Update only when the remaining time changes
      Serial.print("Calibration ends in: ");
      Serial.print(timeRemaining);
      Serial.println(" seconds");
      lastDisplayedTime = timeRemaining;
    }

  }

  dynThreshold = sumCount / calibCount;

  Serial.println("Calibration complete.");
  Serial.print("Dynamic threshold (average lux): ");
  Serial.println(dynThreshold);
}

void loop() {
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
 // Serial.println("motor is running");
  currentRead = veml.readLux();
  Serial.println(currentRead);

if ((abs(dynThreshold  - currentRead)) > 25){ //&& diffBetweenReads < -0.1) {
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
