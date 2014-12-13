void performAction(int index)
{
  switch(index){
    case 0:
    Keyboard.set_key1(KEY_ENTER);
    break;
    case 1:
    Keyboard.set_key1(KEY_F5);
    break;
    case 2:
    Keyboard.set_modifier(MODIFIERKEY_CTRL);
    Keyboard.set_key1(KEY_C);
    break;
    case 3:
    Keyboard.set_modifier(MODIFIERKEY_ALT);
    Keyboard.set_key1(KEY_F4);
    break;
    case 4:
    Keyboard.set_modifier(MODIFIERKEY_CTRL|MODIFIERKEY_SHIFT);
    Keyboard.set_key1(KEY_ESC);
    break;
    case 5:
    Keyboard.set_modifier(MODIFIERKEY_CTRL|MODIFIERKEY_ALT);
    Keyboard.set_key1(KEY_DELETE);
    break;
    case 6:
    Keyboard.set_modifier(MODIFIERKEY_CTRL);
    Keyboard.set_key1(KEY_A);
    break;
    case 7:
    Keyboard.set_key1(KEY_ESC);
    break;
    case 8:
    Keyboard.set_key1(KEY_DELETE);
    break;
    case 9:
    Keyboard.set_key1(KEY_SPACE);
    break;
    case 10:
    Keyboard.set_key1(KEY_Y);
    break;
    case 11:
    Keyboard.set_key1(KEY_N);
    break;
  }
  Keyboard.send_now();
  
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
}
void setup() {
  Serial.begin(9600);
  for(int x=0; x<12; ++x)
  {
    pinMode(x, INPUT_PULLUP);
  }
  delay(500);
}

void loop() {
  for (int x=0; x<12; ++x)
  {
    if (digitalRead(x) == LOW) 
    {
      performAction(x);
      delay(400);
    }
  }
  delay(10);
}
