char* message[] = {
  "one", "two", "three", "four", 
  "five", "six", "seven", "eight", 
  "nine", "ten", "eleven", "twelve"
};

//int buttonDown = 0;

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
    
    break;
    case 4:
    
    break;
    case 5:
    
    break;
    case 6:
    
    break;
    case 7:
    
    break;
    case 8:
    
    break;
    case 9:
    
    break;
    case 10:
    
    break;
    case 11:
    
    break;
    case 12:
    
    break;
  }
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
  char* str;
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


