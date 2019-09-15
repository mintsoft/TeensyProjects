#include <EEPROM.h>

const int maxPin = 16;
byte myKeysToPress[16];
bool keyIsUp[16];

void setup() {
  
  Serial.begin(9600);
  
  initialiseEEPROM();
  loadSettingsFromEEPROM();
  
  for(int x=0; x < maxPin; ++x)
  {
    pinMode(x, INPUT_PULLUP);
    keyIsUp[x] = false;
  }
}

void loop() {
  for (int x=0; x < maxPin; ++x)
  {
    if (digitalRead(x) == LOW && keyIsUp[x])
    {
      keyIsUp[x] = false;
      triggerKeyboardMacro(x);
      Serial.print("Triggered :: ");
      Serial.println(x);
    }
    else
    {
      keyIsUp[x] = true;
    }
  }
}

void triggerKeyboardMacro(int keyIndex) {
  Keyboard.set_key1(myKeysToPress[keyIndex]);
  Keyboard.send_now();
  
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

void initialiseEEPROM() {
  if(EEPROM.read(0) != 255 || EEPROM.read(127) != 255) {
    EEPROM.write(0, 255);
    EEPROM.write(127, 255);
    for(int x=0; x < maxPin; ++x) {
      EEPROM.write(8 + x, (byte)KEY_SPACE);
    }
  }
}

void loadSettingsFromEEPROM() {
  for(int x=0; x < maxPin; ++x) {
    myKeysToPress[x] = EEPROM.read(8 + x);
  }
}

