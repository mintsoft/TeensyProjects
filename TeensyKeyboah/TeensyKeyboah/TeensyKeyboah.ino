#include <EEPROM.h>

#define MAXPIN 16
#define EEPROM_KEYSAVE_OFFSET 8

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
  
  byte inputBuffer[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  unsigned int byteIndex = 0;
  while (Serial.available() && byteIndex < (sizeof(inputBuffer)/sizeof(inputBuffer[0])))
  {
    inputBuffer[byteIndex++] = Serial.read();
  }

  if(inputBuffer[31] != 127)
    return;
  
  if( strncmp("SET ", (char*)inputBuffer,4) == 0 )
  {
      for(int offset=0; offset < MAXPIN; ++offset)
      {
        myKeysToPress[offset] = inputBuffer[offset+4];
      }
  } 
  else if (strncmp("SAVE", (char*)inputBuffer,4) == 0) 
  {
    saveSettingsToEEPROM();
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
      EEPROM.write(EEPROM_KEYSAVE_OFFSET + x, (byte)KEY_SPACE);
    }
  }
}

void loadSettingsFromEEPROM()
{
  for(int x=0; x < MAXPIN; ++x)
  {
    myKeysToPress[x] = EEPROM.read(EEPROM_KEYSAVE_OFFSET + x);
  }
}

void saveSettingsToEEPROM()
{
  for(int x=0; x < MAXPIN; ++x)
  {
     EEPROM.write(EEPROM_KEYSAVE_OFFSET + x, myKeysToPress[x]);
  }
}

