#include <Arduino.h>
//#include "Led.hpp"
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "Equipment.hpp"

#define PUSH_SELECT 10
#define PUSH_UP 11
#define PUSH_DOWN 12
#define PUSH_BACK 13

#define PUSH_DELAY 200

#define IR_EMI_PIN 8
#define IR_REC_PIN 7

#define MAIN_MENU 0
#define EQUIP_MENU 1
#define FUNC_MENU 2
#define NEW_EQUIPMENT_ITEM 0
#define USE_EQUIPMENT_ITEM 1
#define NEW_FUNCTION_ITEM 0

#define EQUIP_MAX_SIZE 5

// IR defines
#define IRpin_PIN PIND
#define IRpin 7
#define MAX_PULSE 65000
#define RESOLUTION 20
//

const short MENU_SELECTED_SIZE[] = {2, 5, MAX_FUNC_SIZE};
const String MAIN_MENU_OPTIONS[] = {"New equipment", "Use equipment"};
const String FUNC_MENU_OPTIONS[] = {"New function"};
const Equipment *equipments[EQUIP_MAX_SIZE];
Equipment *currentEquipment;
unsigned short equipCount = 0;

unsigned short currentMenu = MAIN_MENU;
unsigned short selected = 0;
unsigned short lastSelected = 0;
bool updateUI;

LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7);

//prototypes
void printMainMenu();
void printEquipmentsMenu();
void printFunctionsMenu();
void printRecordingIR(const bool);
void printRecordedIR();
void addEquipment();
void handleEquipmentSelection(const unsigned short);
void clearEquipmentSelection();
void recordIRPulses(Function *);

void setup() {
  lcd.begin(16, 2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.home ();
  lcd.setBacklight(HIGH);

  pinMode(PUSH_SELECT, INPUT);
  digitalWrite(PUSH_SELECT, HIGH);
  pinMode(PUSH_DOWN, INPUT);
  digitalWrite(PUSH_DOWN, HIGH);
  pinMode(PUSH_UP, INPUT);
  digitalWrite(PUSH_UP, HIGH);
  pinMode(PUSH_BACK, INPUT);
  digitalWrite(PUSH_BACK, HIGH);
  updateUI = true;
}

void loop() {
  unsigned int pushDelay = 0;
  lastSelected = selected;
  if(updateUI) {
    switch(currentMenu) {
      case MAIN_MENU:
        printMainMenu();
        break;
      case EQUIP_MENU:
        printEquipmentsMenu();
        break;
      case FUNC_MENU:
        printFunctionsMenu();
        break;
    }
  }

  if(digitalRead(PUSH_DOWN) == LOW) {
    pushDelay = PUSH_DELAY;
    if(selected < MENU_SELECTED_SIZE[currentMenu] - 1) {
      selected++;
      if(currentMenu == EQUIP_MENU)
        handleEquipmentSelection(selected - 1);
    }
  }
  if(digitalRead(PUSH_UP) == LOW) {
    pushDelay = PUSH_DELAY;
    if(selected > 0) {
      selected--;
      if(currentMenu == EQUIP_MENU)
        handleEquipmentSelection(selected + 1);
    }
  }
  if(lastSelected != selected) {
    updateUI = true;
  }

  if(digitalRead(PUSH_SELECT) == LOW) {
    pushDelay = PUSH_DELAY;
    if(currentMenu == MAIN_MENU) {
      switch(selected) {
        case NEW_EQUIPMENT_ITEM:
          addEquipment();
          break;
        case USE_EQUIPMENT_ITEM:
          selected = 0;
          currentMenu = EQUIP_MENU;
          clearEquipmentSelection();
          handleEquipmentSelection(selected);
          updateUI = true;
          break;
      }
    } else if(currentMenu == EQUIP_MENU) {
          currentEquipment = equipments[selected];
          selected = 0;
          currentMenu = FUNC_MENU;
          updateUI = true;
      } else if(currentMenu == FUNC_MENU) {
        if(selected == NEW_FUNCTION_ITEM) {
          Function *f = new Function("x");
          bool added = currentEquipment->addFunction(f);
          printRecordingIR(added);
          if(added) {
            // start recording IR pulses
          }
        }
      }
    }

  if(digitalRead(PUSH_BACK) == LOW) {
    if(currentMenu != MAIN_MENU) {
      currentMenu = MAIN_MENU;
      selected = 0;
      updateUI = true;
    }
  }

  delay(100 + pushDelay);
}

void addEquipment() {
  lcd.clear();
  if(equipCount >= EQUIP_MAX_SIZE) {
    lcd.setCursor(6, 0);
    lcd.print("ERROR");
    lcd.setCursor(0, 1);
    lcd.print("Max 5 equipments");
    delay(2500);
  } else {
    String equip = String("Equip ");
    equip.concat(equipCount + 1);
    equipments[equipCount] = new Equipment(equip);
    equipCount++;

    lcd.setCursor(1, 0);
    lcd.print("New Equipment");
    lcd.setCursor(4, 1);
    lcd.print("created!");
    delay(1500);
  }
  updateUI = true;
}

void handleEquipmentSelection(const unsigned short indexClear) {
  equipments[indexClear]->setSelected(false);
  equipments[selected]->setSelected(true);
}

void clearEquipmentSelection() {
  for(int i = 0; i < EQUIP_MAX_SIZE; i++)
    equipments[i]->setSelected(false);
}

void printMainMenu() {
  lcd.clear();
  for(unsigned short i = 0; i < 2; i++) {
    lcd.setCursor(0, i);
    lcd.print(MAIN_MENU_OPTIONS[i] + (i == selected ? "<-" : ""));
  }
  updateUI = false;
}

void printEquipmentsMenu() {
  lcd.clear();
  if(equipCount == 0) {
    lcd.setCursor(6, 0);
    lcd.print("ERROR");
    lcd.setCursor(1, 1);
    lcd.print("No equipments");
  } else {
    bool update = false;
    if(selected % 2 == 0) {
      update = true;
    }
    unsigned short equipIndex = 0;
    for(unsigned short i = 0; i < 2; i++) {
      lcd.setCursor(0, i);
      equipIndex = i + selected + (!update ? -1 : 0);
      if(equipIndex < MENU_SELECTED_SIZE[currentMenu] && equipIndex < equipCount) {
        String equip = String(equipments[equipIndex]->getName().c_str());
        equip.concat(equipments[equipIndex]->isSelected() ? "<-" : "");
        lcd.print(equip);
      }
    }
  }
  updateUI = false;
}

void printFunctionsMenu() {
  lcd.clear();
  if(selected < 2) {
      lcd.setCursor(0, 0);
      lcd.print(FUNC_MENU_OPTIONS[0] + (0 == selected ? "<-" : ""));
  } else {

  }

  updateUI = false;
}

void printRecordingIR(const bool added) {
  lcd.clear();
  if(!added) {
    lcd.setCursor(6, 0);
    lcd.print("ERROR");
    lcd.setCursor(0, 1);
    lcd.print("Max 2 functions");
    delay(2500);
  } else {
    lcd.setCursor(0,0);
    lcd.print("Recording pulses");
    lcd.setCursor(0,1);
  }

  updateUI = false;
}

void printRecordedIR() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IR code recorded");

  updateUI = false;
}

uint16_t pulses[100][2];
uint8_t currentPulse = 0;

void printPulses() {
  Serial.println("\n\r\n\rReceived: \n\r OFF \t ON");
  // Gera o codigo da tecla pressionada.
  for(uint8_t i = 0; i < currentPulse; i++) {
  Serial.print("delayMicroseconds(");
  Serial.print(pulses[i][0] * RESOLUTION, DEC);
  Serial.print(");\n");
  Serial.print("pulseIR(");
  Serial.print(pulses[i][1] * RESOLUTION, DEC);
  Serial.print(");\n");
  }
}

void recordIRPulses(Function *f) {
  bool cont;

  while(currentPulse < 100) {
    cont = false;
    uint16_t highPulse, lowPulse;
    highPulse = lowPulse = 0;

    while(IRpin_PIN & _BV(IRpin)) {
      highPulse++;
      delayMicroseconds(RESOLUTION);

      if(highPulse >= MAX_PULSE && currentPulse != 0) {
        printPulses();
        currentPulse = 0;
        cont = true;
        break;
      }
    }
    if(cont)
      continue;

    pulses[currentPulse][0] = highPulse;

    while(!(IRpin_PIN & _BV(IRpin))) {
      lowPulse++;
      delayMicroseconds(RESOLUTION);

      if(lowPulse >= MAX_PULSE && currentPulse != 0) {
        printPulses();
        currentPulse = 0;
        cont = true;
        break;
      }
    }
    if(cont)
      continue;

    pulses[currentPulse][1] = lowPulse;
    currentPulse++;
  }
  printRecordedIR();
}
