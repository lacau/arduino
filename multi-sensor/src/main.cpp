#include <Arduino.h>
//#include "Led.hpp"
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define SELECT_PIN 7
#define LIGHT_PIN A2
#define DHT_PIN A3
#define DHT_TYPE DHT11

#define OPT_TEMPERATURE 0
#define OPT_HUMIDITY 1
#define OPT_LIGHT 2
#define OPT_TEXT 3

LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7);
DHT dht(DHT_PIN, DHT_TYPE);

unsigned short currentOption;

// Prototypes
void handleTemperature();
void handleHumidity();
void handleLight();
void handleSimpleWelcome();
void printToDisplay(const char *, const char*);

void setup() {
  lcd.begin(16, 2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.home();
  lcd.setBacklight(HIGH);
  pinMode(SELECT_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);
  digitalWrite(SELECT_PIN, HIGH);
  currentOption = OPT_TEXT;
}

void loop() {
  switch(currentOption) {
    case OPT_TEMPERATURE:
      handleTemperature();
      break;
    case OPT_HUMIDITY:
      handleHumidity();
      break;
    case OPT_LIGHT:
        handleLight();
      break;
    case OPT_TEXT:
      handleSimpleWelcome();
      break;
  }

  if(!digitalRead(SELECT_PIN)) {
    currentOption++;
    if(currentOption % 4 == 0)
      currentOption = 0;

    delay(100);
  }

  delay(100);
}

void handleTemperature() {
  float t = dht.readTemperature();
  char firstLine[16];
  char secondLine[16];
  if(isnan(t)) {
    strcpy(firstLine, "Error on read");
    strcpy(secondLine, "Temperature");
  } else {
    char tem[6];
    dtostrf(t, 4, 1, tem);
    sprintf(firstLine,"Temp: %s C", tem);
    strcpy(secondLine, "");
  }
  printToDisplay(firstLine, secondLine);
  memset(firstLine, 0, 16);
  memset(secondLine, 0, 16);
}

void handleHumidity() {
  float h = dht.readHumidity();
  char firstLine[16];
  char secondLine[16];
  if(isnan(h)) {
    strcpy(firstLine, "Error on read");
    strcpy(secondLine, "Humidity");
  } else {
    char hum[6];
    dtostrf(h, 4, 2, hum);
    sprintf(firstLine,"Humidity: %s%%", hum);
    strcpy(secondLine, "");
  }
  printToDisplay(firstLine, secondLine);
}

void handleLight() {
  int l = 1023 - analogRead(LIGHT_PIN);
  char firstLine[16];
  char secondLine[16];
  if(isnan(l)) {
    strcpy(firstLine, "Error on read");
    strcpy(secondLine, "Light");
  } else {
    char lig[6];
    dtostrf(l, 4, 3, lig);
    sprintf(firstLine,"Light: %d", l);
    strcpy(secondLine, "");
  }
  printToDisplay(firstLine, secondLine);
}

void handleSimpleWelcome() {
  char firstLine[16];
  strcpy(firstLine, "Welcome");
  printToDisplay(firstLine, "");
}

void printToDisplay(const char *firstLine, const char *secondLine) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(firstLine);
  if(secondLine != NULL) {
    lcd.setCursor(0, 1);
    lcd.print(secondLine);
  }
  memset(firstLine, 0, sizeof firstLine);
  memset(secondLine, 0, sizeof secondLine);
}
