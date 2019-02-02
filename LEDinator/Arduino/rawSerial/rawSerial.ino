
void setup() {
  Serial.begin(9600);
  for (int i=0; i<12; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {
  char received_char;
  int pin_number;

  while( Serial.available() > 0 ) {
    received_char = Serial.read();

    //Serial.print("Received Something: ");
    //Serial.println(received_char);
    
    if(received_char < 0) {
      continue;
    }
    
    pin_number = received_char - 0x30;
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

