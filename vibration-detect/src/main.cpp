#include <Arduino.h>

#define VIB_SENSOR_PIN 0
#define RED_LED_PIN 7
#define GREEN_LED_PIN 8

void setup() {
  pinMode(VIB_SENSOR_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
}
