#include<Wire.h>
#define CYCLE_TIME 20000


struct Road {
//  unsigned int id;
  unsigned carCount;
  unsigned allocatedTime;
  unsigned long long atWhatTimeItWillTurnRed;
} roads[4];

const int CAR_IN[] = {0 , 2, 12, 6};
const int CAR_OUT[] = {4, 3, 5, 7};
const int GREEN[] = {8, 9, 10, 11};
//const int YELLOW[] = {12, 13, A0, A1};
const int RED[] = {A2, A3, A4, A5};
bool flagIn[4] = {false};
bool flagOut[4] = {false};
bool valueIn[4] = {false};
bool valueOut[4] = {false};
unsigned long int totalCars = 0;

int compare(const void* a, const void* b) {
  const int* x = (int*) a;
  const int* y = (int*) b;
  if (*x > *y)
    return 1;
  else if (*x < *y)
    return -1;

  return 0;
}

void turnGreen(int index) {
  digitalWrite(RED[index], LOW);
//  digitalWrite(YELLOW[index], HIGH);
//  delay(2000);
//  digitalWrite(YELLOW[index], LOW);
  digitalWrite(GREEN[index], HIGH);
}

void turnRed(int index) {
  digitalWrite(GREEN[index], LOW);
//  digitalWrite(YELLOW[index], HIGH);
//  delay(2000);
//  digitalWrite(YELLOW[index], LOW);
  digitalWrite(RED[index], HIGH);
}


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++){
//    roads[0].id = i;
    roads[i].carCount = 1;
//    roads[i].allocatedTime = 0;
    pinMode(CAR_IN[i], INPUT);
    pinMode(CAR_OUT[i], INPUT);
    pinMode(GREEN[i], OUTPUT);
//    pinMode(YELLOW[i], OUTPUT);
    pinMode(RED[i], OUTPUT);

    digitalWrite(GREEN[i], LOW);
//    digitalWrite(YELLOW[i], LOW);
    digitalWrite(RED[i], HIGH);
  }
}

//unsigned loopCount = 0;
double timeCounter = 0;
double timeTillStuck = 0;
unsigned roadsDoneTillNow = 0;
unsigned timeRemaining = CYCLE_TIME;

void loop() {
//  Serial.print("hello");
//  if (loopCount == 0) {
//    for (int i=0; i<4; i++) {
//      turnGreen(i);
//      delay(200);
//      turnRed(i);
//    }
//  }
//
//  loopCount++;

  for (int i = 0; i < 4; i++) {
    
    // count ++
    valueIn[i] = !digitalRead(CAR_IN[i]);
    if (valueIn[i]) {
      flagIn[i] = true;
    }
   // Serial.print("dhukse");
    if ((flagIn[i] == true ) && (valueIn[i] == false)) {
      roads[i].carCount++;
      totalCars++;
//      Serial.print("here");
      Serial.println("Road " + String(i) + " Cars " + String(roads[i].carCount));
      flagIn[i] = false;
    }

    // count --
    valueOut[i] = !digitalRead(CAR_OUT[i]);
    if (valueOut[i]) {
      flagOut[i] = true;
    }
    if ((flagOut[i] == true ) && (valueOut[i] == false)) {
      roads[i].carCount--;
      totalCars--;
//      Serial.print("there");
      Serial.println("Road " + String(i) + " Cars " + String(roads[i].carCount));
      flagOut[i] = false;
    }
  }

  // by this time I have the car counts of all the roads
  // we have to implement algorithms now

  // timeRemaining = CYCLE_TIME
//  unsigned timeRemaining = CYCLE_TIME;
  // sort
//  for (int i = 0; i < 4; i++) {
    
//    qsort(roads, 3-i, sizeof(unsigned), compare);    
//    for (int k = 0; k < 4-i; k++) {
//      roads[k].allocatedTime = timeRemaining * roads[k].carCount / totalCars;
//    }
//    timeTillStuck = timeCounter + roads[3-i].allocatedTime;
//    // Green Light for the max car road
//    turnGreen(3-i);
//    timeRemaining -= roads[3-i].allocatedTime;
//    totalCars -= roads[3-i].carCount;
//    // delay
//    turnRed(3-i);
//  }

  if(timeCounter >= timeTillStuck) {
    for (int k=0; k<4; k++) {
      turnRed(k);
    }
    qsort(roads, 3-roadsDoneTillNow, sizeof(unsigned), compare);    
    for (int k = 0; k <= 3-roadsDoneTillNow; k++) {
      roads[k].allocatedTime = timeRemaining * roads[k].carCount / totalCars;
      Serial.println(roads[k].carCount / totalCars);
    }
    timeRemaining -= roads[3-roadsDoneTillNow].allocatedTime;
    timeTillStuck = timeCounter + roads[3-roadsDoneTillNow].allocatedTime/1000;
    // Green Light for the max car road
    turnGreen(3-roadsDoneTillNow);
    roadsDoneTillNow++;
  
    if (roadsDoneTillNow == 4) {
      roadsDoneTillNow = 0;
      timeRemaining = CYCLE_TIME;
      totalCars = 0;
    }

    for (int i=0; i<4; i++) {
      Serial.println("Road " + String(i) + " Cars " + String(roads[i].carCount));
    }
  }

  delay(10);
  timeCounter += 0.01;
//  Serial.print(timeCounter, 2);
//  Serial.print(" ");
//  Serial.println(timeTillStuck, 2);
}
