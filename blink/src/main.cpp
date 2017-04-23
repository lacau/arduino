#include <Arduino.h>
#include "Led.hpp"

const unsigned short LED_GREEN_PIN = 13;
const unsigned short LED_RED_PIN = 12;

Led *LED_GREEN = new Led(LED_GREEN_PIN, HIGH);
Led *LED_RED = new Led(LED_RED_PIN, HIGH);

void setup() {
  pinMode(LED_GREEN->getPin(), OUTPUT);
  pinMode(LED_RED->getPin(), OUTPUT);
}

void loop() {
  digitalWrite(LED_GREEN->getPin(), LED_GREEN->getMode());
  digitalWrite(LED_RED->getPin(), LED_RED->getMode());
  delay(500);
  LED_RED->switchMode();
  digitalWrite(LED_RED->getPin(), LED_RED->getMode());
  delay(500);
  LED_GREEN->switchMode();
  digitalWrite(LED_GREEN->getPin(), LED_GREEN->getMode());
  LED_RED->switchMode();
  digitalWrite(LED_RED->getPin(), LED_RED->getMode());
  delay(500);
  LED_RED->switchMode();
  digitalWrite(LED_RED->getPin(), LED_RED->getMode());
  delay(500);
  LED_GREEN->switchMode();
  LED_RED->switchMode();
}
