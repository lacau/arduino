#include <Arduino.h>

#define VIB_SENSOR_PIN 2
#define RED_LED_PIN 7
#define GREEN_LED_PIN 8

int vibration = 0;

void setup() {
  pinMode(VIB_SENSOR_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, HIGH);
  Serial.begin(9600);
}

void loop() {
  vibration = digitalRead(VIB_SENSOR_PIN);
  Serial.println(vibration);
  if(vibration == HIGH) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    delay(1000);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
  delay(100);
}
