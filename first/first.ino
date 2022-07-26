#include<Wire.h>

#define CYCLE_TIME 2000

struct Road {
//  unsigned int id;
  unsigned int carCount;
  unsigned int allocatedTime;
} roads[4];

const int IN[] = {10 , 11, 12, 13};
const int OUT[] = {6, 7, 8, 9};
bool flag1[4] = {false};
bool flag2[4] = {false};
bool value[4];
unsigned long int totalCars = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++){
//    road[0].id = i;
    road[i].carCount = 0;
    road[i].allocatedTime = 0;
    pinMode(IN[i], INPUT);
    pinMode(OUT[i], OUTPUT)
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    // count --
    value[i] = !digitalRead(IN[i]);

    if (value[i]) {
      flag1[i] = true;
    }
  
    if ((flag1[i] == true ) && (value[i] == false)) {
      road[i].carCount++;
      totalCars++;
      Serial.print(i);
      Serial.print(" \n");
      Serial.print(road[i].carCount);
  
      flag1[i] = false;
    }

    // count --
    value[i] = !digitalRead(OUT[i]);

    if (value[i]) {
      flag2[i] = true;
    }
  
    if ((flag2[i] == true ) && (value[i] == false)) {
      road[i].carCount--;
      totalCars--;
      Serial.print(i);
      Serial.print(" \n");
      Serial.print(road[i].carCount);
  
      flag2[i] = false;
    }
  }

  // by this time I have the car counts of all the roads
  // we have to implement algorithms now

  // timeRemaining = CYCLE_TIME
  // sort
  // ratio

  // loop begin 4 times 4321
  // find max
  // delay allocated time
  // erase
  
  delay(100);
}
