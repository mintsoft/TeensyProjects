#define ASCII_DIGIT_OFFSET 0x30;

char buffer[255];
int y;

void setup() {
  Serial.begin(115200);
  for (int i=0; i<10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  y = 0;
}

//in cmd::  mode com7 BAUD=9600 PARITY=n DATA=8 STOP=1 && echo 3 > com7

void loop() {
  char received_char;
  int pin_number;
  
  while( Serial.available() > 0 ) {
    received_char = Serial.read();

    //Serial.print("Received Something: ");
    //Serial.println(received_char);
    buffer[y%255] = received_char;
    y++;
    
    pin_number = received_char - ASCII_DIGIT_OFFSET;
    
    if(pin_number < 0 || pin_number > 9) {
      continue;
    }
    
    if(pin_number == 9) {
      Serial.println("I have seen: ");
      for(int x=0; x<255; ++x) {
        Serial.print("'");
        Serial.print(buffer[x]);
        Serial.println("'");
      }
      Serial.println("I'm done");
    }
    for (int i=0; i<10; i++) {
      if(i == pin_number) {
        //Serial.print("Setting low pin: ");
        //Serial.println(i);
        digitalWrite(i, LOW);
      } else {
        //Serial.print("Setting high pin: ");
        //Serial.println(i);
        digitalWrite(i, HIGH);
      }
    }
  }

}

