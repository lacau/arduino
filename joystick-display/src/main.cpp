#include <Arduino.h>
//#include "Led.hpp"
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// const unsigned short LED_GREEN_PIN = 13;
// const unsigned short LED_RED_PIN = 10;

// Led *LED_GREEN = new Led(LED_GREEN_PIN, HIGH);
// Led *LED_RED = new Led(LED_RED_PIN, HIGH);
LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7);

const unsigned short JOY_X = 0;
const unsigned short JOY_Y = 1;
const unsigned short JOY_RESET = 4;

int x = 0;
int y = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.home ();
  lcd.setBacklight(HIGH);
  pinMode(JOY_RESET, INPUT);
  digitalWrite(JOY_RESET, HIGH);
}

int treatAnalogInput(int value) {
  return map(value, 0, 1023, -5, 5);
}

void loop() {
  x += treatAnalogInput(analogRead(JOY_X));
  lcd.setCursor(0,0);
  lcd.print("x: " + String(x));

  y += treatAnalogInput(analogRead(JOY_Y));
  lcd.setCursor(0,1);
  lcd.print("y: " + String(y));

  if(digitalRead(JOY_RESET) == LOW) {
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("reseting");
    delay(1000);
    lcd.setBacklight(LOW);
    lcd.clear();
    delay(300);
    lcd.setBacklight(HIGH);
    x = 0;
    y = 0;
  }

  delay(100);
  lcd.clear();
}
