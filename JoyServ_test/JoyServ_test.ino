#include <ESP32Servo.h>

#define NOISE 25;

Servo myServo1;
int pos1 = 0;

int servoPin1 = 26;

Servo myServo2;
int pos2 = 0;

int servoPin2 = 27;

int joyxPin = 34;
float xLow = 0;
float xHigh = 0;


int joyyPin = 35;
float yLow = 0;
float yHigh = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(servoPin1,OUTPUT);
  pinMode(servoPin2,OUTPUT);

  myServo1.setPeriodHertz(50);
  myServo1.attach(servoPin1);

  myServo2.setPeriodHertz(50);
  myServo2.attach(servoPin2);

  myServo1.write(pos1);
  myServo2.write(pos2);
  
  pinMode(joyxPin,INPUT);
  pinMode(joyyPin,INPUT);

  delay(10);
  float curX = analogRead(joyxPin);
  float curY = analogRead(joyyPin);

  xLow = curX - NOISE;
  xHigh = curX + NOISE;

  yLow = curY - NOISE;
  yHigh = curY + NOISE;

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
    yAdd = 1;
  }
  if(y < yLow){
    yAdd = -1;
  }

  if(xAdd == 1 && pos1 <180){
    pos1 += xAdd;
  }
  if(xAdd == -1 && pos1 > 0){
    pos1 += xAdd;
  }

  if(yAdd == 1 && pos2 < 180){
    pos2 += yAdd;
  }
  if(yAdd == -1 && pos2 > 0){
    pos2 += yAdd;
  }

  myServo1.write(pos1);
  delay(20);
  myServo2.write(pos2);
  delay(20);

  Serial.print("pos1: " + String(pos1) + " x: " + String(x));

  Serial.print("  pos2: " + String(pos2) + " y: " + String(y) + "\n");
  
}
