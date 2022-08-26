//#include <SoftwareSerial.h>
#include<Wire.h>
#include <Servo.h>
#define CYCLE_TIME 20000

#define UP_ANGLE 20
#define DOWN_ANGLE 70

//arduino part
//SoftwareSerial serial(12, 13);
//const int YELLOW[] = {8,9,10,11};
//train part
//const int trainID = 0;
const int TRAIN_LEFT = 2;
const int TRAIN_RIGHT = 3;
bool flagLeft = false;
bool flagRight = false;
bool valueLeft = 0;
bool valueRight = 0;
bool isTrain = false;
//servo motor part
//const int servoPin1 = A5;
//const int servoPin2 = A4;
//Servo servo1, servo2;
const int servoPin = A5;
Servo servo;



void setup() {
//  serial.begin(9600);
  Serial.begin(9600);
//  light
//  for (int i = 0; i < 4; i++) {
//    pinMode(YELLOW[i], OUTPUT);
//    digitalWrite(YELLOW[i], LOW);
//  }
  //train
  pinMode(TRAIN_LEFT, INPUT);
  pinMode(TRAIN_RIGHT, INPUT);
  //servo motor
//  servo1.attach(servoPin1);
//  servo2.attach(servoPin2);
  servo.attach(servoPin);  

  servo.write(UP_ANGLE);
}

void toggleBarricade() {
    if (isTrain) {
      isTrain = false;
      Serial.println("goingup");
      servo.write(UP_ANGLE);
    } else {
      isTrain = true;
      Serial.println("comingdown");
      servo.write(DOWN_ANGLE);
    }
}

void loop() {
  //train part
  // right is positive edge triggered
  valueRight = !digitalRead(TRAIN_RIGHT);
  if (valueRight == false) {
    flagRight = true;
  }
  if ((flagRight == true ) && (valueRight == true)) {
    Serial.println("right sensor obstacle detected");
    toggleBarricade();
    flagRight = false;

    delay(1000);
  }
  
  // left is negative edge triggered
  valueLeft = !digitalRead(TRAIN_LEFT);
  if (valueLeft) {
    flagLeft = true;
  }
  if ((flagLeft == true ) && (valueLeft == false)) {
    Serial.println("left sensor obstacle detected");
    toggleBarricade();
    flagLeft = false;

    delay(1000);
  }
  
  

  // send train status over bluetooth
//  if (isTrain) serial.print("true");
//  else serial.print("false");

  delay(10);
}
