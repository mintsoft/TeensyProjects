#include <EEPROM.h>

#define MAXPIN 16

byte myKeysToPress[MAXPIN];
bool keyIsUp[MAXPIN];

void setup()
{
  Serial.begin(9600);
  
  initialiseEEPROM();
  loadSettingsFromEEPROM();
  
  for(int x=0; x < MAXPIN; ++x)
  {
    pinMode(x, INPUT_PULLUP);
    keyIsUp[x] = false;
  }
}

void loop()
{
  for (int x=0; x < MAXPIN; ++x)
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

void triggerKeyboardMacro(int keyIndex)
{
  Keyboard.set_key1(myKeysToPress[keyIndex]);
  Keyboard.send_now();
  
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

void initialiseEEPROM()
{
  if(EEPROM.read(0) != 255 || EEPROM.read(127) != 255)
  {
    EEPROM.write(0, 255);
    EEPROM.write(127, 255);
    for(int x=0; x < MAXPIN; ++x)
    {
      EEPROM.write(8 + x, (byte)KEY_SPACE);
    }
  }
}

void loadSettingsFromEEPROM()
{
  for(int x=0; x < MAXPIN; ++x)
  {
    myKeysToPress[x] = EEPROM.read(8 + x);
  }
}

