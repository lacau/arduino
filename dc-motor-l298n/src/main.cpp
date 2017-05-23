#include <Arduino.h>

#define M2_DIR_PIN 4
#define M2_SPD_PIN 5
#define M1_SPD_PIN 6
#define M1_DIR_PIN 7

void setup() {
  pinMode(M2_DIR_PIN, OUTPUT);
}

void loop() {
  for(int i = 255; i >=0 ; i--) {
    digitalWrite(M1_DIR_PIN, HIGH);
    digitalWrite(M2_DIR_PIN, LOW);
    analogWrite(M1_SPD_PIN, i);
    analogWrite(M2_SPD_PIN, i);
    if(i == 0) delay(1000);
    delay(30);
  }
  delay(1000);
}
