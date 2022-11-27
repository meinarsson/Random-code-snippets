/* This minimal example shows how to get single-shot range
measurements from the VL6180X.
The range readings are in units of mm. */

#include <Wire.h>
#include <VL6180X.h>

const int redLed = 12;
const int yellowLed = 11;
const int greenLed = 10;

VL6180X sensor;

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  sensor.init();
  sensor.configureDefault();
  sensor.setTimeout(500);
  /* sensor.startRangeContinuous(500); */
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
  Serial.println("Setup done");
}

void loop() 
{ 
  uint8_t range;
  range=sensor.readRangeSingleMillimeters();
  /* Serial.print(sensor.readRangeMillimeters()); */
  /* Serial.print(sensor.readRangeContinuousMillimeters()); */

  if(range == 255) {
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
  } 
  if(range < 50) {
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
  else if (range < 255) {
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(greenLed, LOW);
  }
  Serial.print(range);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  
  Serial.println();
}
