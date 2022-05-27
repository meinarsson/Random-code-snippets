
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define LED_COUNT 2

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ400);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Endast röd lyser
  strip.setPixelColor(0, 255, 0, 0);
  // Endast blå lyser
  strip.setPixelColor(1, 0, 0, 255);
  strip.show();
  delay(1000);
  // Endast röd lyser
  strip.setPixelColor(0, 0, 0, 255);
  // Endast blå lyser
  strip.setPixelColor(1, 0, 255, 0);
  strip.show();
  delay(1000);
  // Endast grön lyser
  strip.setPixelColor(0, 0, 255, 0);
  // Endast blå lyser
  strip.setPixelColor(1, 255, 0, 0);
  strip.show();
  delay(1000);
}
