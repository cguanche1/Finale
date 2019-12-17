
//Setting joystick-related button and LED
int joyButPin = 33;
int joyLedPin = 18;
int ljstate = HIGH;

//Setting other buttons up
int oneButPin = 34;
int oneLedPin = 23;
int lostate = HIGH;

int twoButPin = 35;
int twoLedPin = 22;
int lwstate = HIGH;

int thrButPin = 32;
int thrLedPin = 1;
int lhstate = HIGH;



void setup() {
  // put your setup code here, to run once:
  pinMode(joyButPin, INPUT_PULLUP);
  pinMode(joyLedPin, OUTPUT);
  
  digitalWrite(joyLedPin, LOW);

  pinMode(oneButPin, INPUT_PULLUP);
  pinMode(oneLedPin, OUTPUT);

  digitalWrite(oneLedPin,LOW);  

  pinMode(twoButPin, INPUT_PULLUP);
  pinMode(twoLedPin, OUTPUT);

  digitalWrite(twoLedPin, LOW);

  pinMode(thrButPin, INPUT_PULLUP);
  pinMode(thrLedPin, OUTPUT);

  digitalWrite(thrLedPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(thrButPin);
  /*while(reading == LOW){
    reading = digitalRead(oneButPin);
    digitalWrite(oneLedPin,HIGH);
  }
  digitalWrite(oneLedPin,LOW);

  reading = digitalRead(twoButPin);

  while(reading == LOW){
    reading = digitalRead(twoButPin);
    digitalWrite(twoLedPin,HIGH);
  }
  digitalWrite(twoLedPin,LOW);
  */

  while(reading == LOW){
    reading = digitalRead(thrButPin);
    digitalWrite(thrLedPin,HIGH);
  }
  digitalWrite(thrLedPin,LOW);
  
  reading = digitalRead(joyButPin);
  
  while(reading == LOW){
    reading = digitalRead(joyButPin);
    digitalWrite(joyLedPin,HIGH);
  }
  digitalWrite(joyLedPin,LOW);
  

  if(digitalRead(oneButPin) == HIGH && digitalRead(twoButPin) == HIGH &&
      digitalRead(thrButPin) == HIGH && digitalRead(joyButPin) == HIGH){
    return;
      }
}
