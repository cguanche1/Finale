#include <ESP32Servo.h>

//Defines an approximate range within which changes to the joystick's value should be ignored.
#define NOISE 25;

//State machine variable states;
#define ONE 0
#define TWO 1
#define THR 2
#define JOY 3

//Adds the servo responsible for horizontal motion
Servo hServ;
int hpos = 60;
int hleft = 82;
int hright = 36;

int hPin = 17;

//Adds the servo responsible for vertical motion
Servo vServ;
int vpos = 23;
int vhigh = 0;
int vlow = 48;

int vPin = 5;

//Setting joystick X
int joyxPin = 27;
float xLow = 0;
float xHigh = 0;

//Setting Joystick Y
int joyyPin = 14;
float yLow = 0;
float yHigh = 0;

//Setting joystick-related button and LED
int joyButPin = 33;
int joyLedPin = 18;
int ljstate = HIGH;

//Setting other buttons up
int oneButPin = 25;
int oneLedPin = 23;
int lostate = HIGH;

int twoButPin = 26;
int twoLedPin = 22;
int lwstate = HIGH;

int thrButPin = 32;
int thrLedPin = 21;
int lhstate = HIGH;


int lasLedPin = 15;

//Create variables for state machine
int state = ONE;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  //Set all of the pinmodes, connect the motors and define the noise ranges for the joystick
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

  pinMode(lasLedPin, OUTPUT);

  digitalWrite(lasLedPin,HIGH);


  //Initialize button-shaped switches so they act like damn buttons.
  
  if(digitalRead(oneButPin) == LOW){
    Serial.print("one isn't right\n");
    delay(20);
    if(digitalRead(oneButPin) == LOW){
      while(digitalRead(oneButPin) == LOW){
        digitalWrite(oneLedPin, HIGH);
        delay(10);
      }
      digitalWrite(oneLedPin,LOW);
    }
  }
  Serial.print("Past one\n");

  if(digitalRead(twoButPin) == LOW){
    delay(20);
    if(digitalRead(twoButPin) == LOW){
      Serial.print("Two isn't right\n");
      while(digitalRead(twoButPin) == LOW){
        digitalWrite(twoLedPin, HIGH);
        delay(10);
      }
      digitalWrite(twoLedPin,LOW);
    }
  }
  Serial.print("Past two\n");

  if(digitalRead(thrButPin) == LOW){
    delay(20);
    if(digitalRead(thrButPin) == LOW){
      Serial.print("Three isn't right\n");
      while(digitalRead(thrButPin) == LOW){
        digitalWrite(thrLedPin, HIGH);
        delay(10);
      }
      digitalWrite(thrLedPin,LOW);
    }
  }
  Serial.print("Past three\n");

  if(digitalRead(joyButPin) == LOW){
    delay(20);
    if(digitalRead(joyButPin) == LOW){
      Serial.print("Joy isn't right\n");
      while(digitalRead(joyButPin) == LOW){
        digitalWrite(joyLedPin, HIGH);
        delay(10);
      }
      digitalWrite(joyLedPin,LOW);
    }
  }
  Serial.print("Past joy\n");

  
  
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //Serial.print("x: " + String(analogRead(joyxPin)) + " y: " + String(analogRead(joyyPin)) + "\n");

  switch(state){
    case ONE:
      {
      int x = (int)random(-1,2);
      int y = (int)random(-1,2);

      if((x == 1 && hpos < hleft) || (x == -1 && hpos > hright)){
        hpos += x;
      }

      if((y == 1 && vpos < vlow) || (y == -1 && vpos > vhigh)){
        vpos += y;
      }

      hServ.write(hpos);
      vServ.write(vpos);
      delay(50);
      }
      break;
      
    case TWO:
      {
      int x = (int)random(-1,2);
      int y = (int)random(-1,2);

      if((x == 1 && hpos < hleft) || (x == -1 && hpos > hright)){
        hpos += (2 * x);
      } 

      if((y == 1 && vpos < vlow) || (y == -1 && vpos > vhigh)){
        vpos += (2 * y);
      }

      hServ.write(hpos);
      vServ.write(vpos);
      delay(50);
      }
      break;
      
    case THR:
      {
      int x = (int)random(-1,2);
      int y = (int)random(-1,2);

      if((x == 1 && hpos < hleft) || (x == -1 && hpos > hright)){
        hpos += (3 * x);
      } 

      if((y == 1 && vpos < vlow) || (y == -1 && vpos > vhigh)){
        vpos += (3 * y);
      }

      hServ.write(hpos);
      vServ.write(vpos);
      delay(50);
      }
      
      break;

    case JOY:
      {
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

      
      if(xAdd == 1 && hpos < hleft){
        hpos += xAdd;
      }
      if(xAdd == -1 && hpos > hright){
        hpos += xAdd;
      }

      if(yAdd == 1 && vpos < vlow){
        vpos += yAdd;
      }
      if(yAdd == -1 && vpos > vhigh){
        vpos += yAdd;
      }

      hServ.write(hpos);
      delay(20);
      vServ.write(vpos);
      delay(20);

      Serial.print("hpos: " + String(hpos));

      Serial.print("  vpos: " + String(vpos) + "\n");
      }
      break;
  }

  if(digitalRead(oneButPin) != lostate){
    delay(20);
    if(digitalRead(oneButPin) != lostate){
      lostate = digitalRead(oneButPin);
      state = ONE;
    }
  }
  if(digitalRead(twoButPin) != lwstate){
    delay(20);
    if(digitalRead(twoButPin) != lwstate){
      lwstate = digitalRead(twoButPin);
      state = TWO;
    }
  }
  if(digitalRead(thrButPin) != lhstate){
    delay(20);
    if(digitalRead(thrButPin) != lhstate){
      lhstate = digitalRead(thrButPin);
      state = THR;
    }
  }
  if(digitalRead(joyButPin) != ljstate){
    delay(20);
    if(digitalRead(joyButPin) != ljstate){
      lostate = digitalRead(joyButPin);
      state = JOY;
    }
    
  }

  int pins[] = {oneLedPin,twoLedPin,thrLedPin,joyLedPin};
  for(int i = 0; i < 4; i ++){
      if(state != i){
          digitalWrite(pins[i],HIGH);
      }
      else{
          digitalWrite(pins[i],LOW);
      }
    }
  }
