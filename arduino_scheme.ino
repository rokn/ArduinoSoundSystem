#define START_PIN 2
#define END_PIN 10

void setup() {
  Serial.begin(9600);
  int i;
  for(i = START_PIN; i <= END_PIN; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  int i;
  
  if(Serial.read() == 0xff){
      int numb = Serial.read();

      for(int i = START_PIN; i <= END_PIN; i++)
      {
          if(numb > i - START_PIN){
            digitalWrite(i, HIGH);
          } else {
            digitalWrite(i, LOW);
          }
      }
  }

  delay(30);
}
