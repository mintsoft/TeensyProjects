#define GREEN_BUTTON 1
#define STOPPER 0

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
  for(int x=0; x<2; ++x)
  {
    pinMode(x, INPUT_PULLUP);
  }
  delay(500);
}

int latches[2] = {0,0};
int actions[2] = {0,0};
void loop() {

  if(digitalRead(STOPPER) != LOW)
  {
    if(!latches[STOPPER])
      actions[STOPPER] = 1;
    latches[STOPPER] = 1;
  }
  else
  {
    latches[STOPPER] = 0;
  }
  if(digitalRead(GREEN_BUTTON) == LOW)
  {
    if(!latches[GREEN_BUTTON])
      actions[GREEN_BUTTON] = 1;
    latches[GREEN_BUTTON] = 1;
  }
  else
  {
    latches[GREEN_BUTTON] = 0; 
  }

  for(int x=0; x< 2; ++x)
  {
    if(actions[x])
    {
      actions[x] = 0;
      if(x == GREEN_BUTTON && latches[STOPPER])
      {
        continue;
      }
      performAction(x);
    }
  }  
  delay(10);
}
