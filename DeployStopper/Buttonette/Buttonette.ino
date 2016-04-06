void performAction(int index)
{
  switch(index){
    case 0:
      Keyboard.set_modifier(MODIFIERKEY_ALT|MODIFIERKEY_CTRL|MODIFIERKEY_SHIFT);
      Keyboard.set_key1(KEY_END);
    break;
    case 1:
      Keyboard.set_modifier(MODIFIERKEY_ALT|MODIFIERKEY_CTRL|MODIFIERKEY_SHIFT);
      Keyboard.set_key1(KEY_INSERT);
    break;
    default:
      return;
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
