#define ASCII_DIGIT_OFFSET 0x30;
#define RED_PIN 11
#define GREEN_PIN 12
#define BLUE_PIN 13

char buffer[255];

int y;
int red;
int blue;
int green;

void setup() {
  Serial.begin(115200);
  for (int i=0; i<10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  y = 0;
  red = 0;
  blue = 0;
  green = 0;
  memset(buffer,0,sizeof(buffer));
}

//in cmd::  mode com7 BAUD=9600 PARITY=n DATA=8 STOP=1 && echo 3 > com7

void loop() {
  char received_char;
  while( Serial.available() > 0 ) {
    received_char = Serial.read();
    
    buffer[y] = received_char;
    y = y+1%255;
    
    if(received_char != '\n')
      continue;
   
    sscanf(buffer, "%d %d %d", &red, &green, &blue);

    y=0;
    memset(buffer,0,sizeof(buffer));
    
    red %= 256;
    green %= 256;
    blue %= 256;
        
    analogWrite(GREEN_PIN, green);
    analogWrite(RED_PIN, red);
    analogWrite(BLUE_PIN, blue);
  }
}

