#define ASCII_DIGIT_OFFSET 0x30;
#define RED_PIN 10
#define GREEN_PIN 11
#define BLUE_PIN 9

char buffer[255];

int y;
int red;
int blue;
int green;

void setup() {
  Serial.begin(115200);
  for (int i=9; i<12; i++) {
    pinMode(i, OUTPUT);
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
    Serial.print("Received: ");
    Serial.println(received_char);
    buffer[y] = received_char;
    y = y+1%255;
    
    if(received_char != '\n' && received_char != ';')
      continue;

    Serial.print("buffer: '");
    Serial.print(buffer);
    Serial.println("'");
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

