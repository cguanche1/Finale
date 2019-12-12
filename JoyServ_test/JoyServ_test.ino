#include <ESP32Servo.h>

#define NOISE 25;

Servo hServ;
int hpos = 60;

int hPin = 17;

Servo vServ;
int vpos = 23;

int vPin = 5;

int joyxPin = 25;
float xLow = 0;
float xHigh = 0;


int joyyPin = 26;
float yLow = 0;
float yHigh = 0;

int joyButPin = 33;
int joyLedPin = 18;

int oneButPin = 34;
int oneLedPin = 23;

int twoButPin = 35;
int twoLedPin = 22;

int thrButPin = 32;
int thrLedPin = 1;


int lasLedPin = 15;

void setup() {
  // put your setup code here, to run once:
  pinMode(hPin,OUTPUT);
  pinMode(vPin,OUTPUT);

  hServ.setPeriodHertz(50);
  hServ.attach(hPin);

  vServ.setPeriodHertz(50);
  vServ.attach(vPin);

  hServ.write(hpos);
  vServ.write(vpos);
  
  pinMode(joyxPin,INPUT);
  pinMode(joyyPin,INPUT);

  delay(10);
  float curX = analogRead(joyxPin);
  float curY = analogRead(joyyPin);

  xLow = curX - NOISE;
  xHigh = curX + NOISE;

  yLow = curY - NOISE;
  yHigh = curY + NOISE;

  pinMode(joyButPin, INPUT_PULLUP);
  pinMode(joyLedPin, OUTPUT);
  
  digitalWrite(joyLedPin, HIGH);

  pinMode(oneButPin, INPUT_PULLUP);
  pinMode(oneLedPin, OUTPUT);

  digitalWrite(oneLedPin,LOW);  

  pinMode(twoButPin, INPUT_PULLUP);
  pinMode(twoLedPin, OUTPUT);

  digitalWrite(twoLedPin, HIGH);

  pinMode(thrButPin, INPUT_PULLUP);
  pinMode(thrLedPin, OUTPUT);

  digitalWrite(thrLedPin,HIGH);

  pinMode(lasLedPin, OUTPUT);

  digitalWrite(lasLedPin,HIGH);

  
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //Serial.print("x: " + String(analogRead(joyxPin)) + " y: " + String(analogRead(joyyPin)) + "\n");

  float x = analogRead(joyxPin);
  float y = analogRead(joyyPin);

  int xAdd = 0;
  int yAdd = 0;

  if(x > xHigh){
    xAdd = 1;
  }
  if(x < xLow){
    xAdd = -1;
  }

  if(y > yHigh){
    yAdd = -1;
  }
  if(y < yLow){
    yAdd = 1;
  }

  if(xAdd == 1 && hpos < 82){
    hpos += xAdd;
  }
  if(xAdd == -1 && hpos > 36){
    hpos += xAdd;
  }

  if(yAdd == 1 && vpos < 48){
    vpos += yAdd;
  }
  if(yAdd == -1 && vpos > 0){
    vpos += yAdd;
  }

  hServ.write(hpos);
  delay(20);
  vServ.write(vpos);
  delay(20);

  Serial.print("hpos: " + String(hpos));

  Serial.print("  vpos: " + String(vpos) + "\n");
  
}
