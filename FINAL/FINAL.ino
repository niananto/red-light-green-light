#include<Wire.h>
#define CYCLE_TIME 20000

struct Road {
  unsigned int id;
  unsigned carCount;
  double allocatedTime;
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

void bubbleSort(struct Road arr[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j].carCount > arr[j + 1].carCount) {
        struct Road temp;
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void turnGreen(int index) {
  digitalWrite(RED[index], LOW);
  digitalWrite(GREEN[index], HIGH);
}

void turnRed(int index) {
  digitalWrite(GREEN[index], LOW);
  digitalWrite(RED[index], HIGH);
}


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    roads[i].id = i;
    roads[i].carCount = 5 - i;
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

double timeCounter = 0;
double timeTillStuck = 0;
unsigned roadsDoneTillNow = 0;
double timeRemaining = CYCLE_TIME;

void loop() {

  for (int i = 0; i < 4; i++) {
    // count ++
    valueIn[i] = !digitalRead(CAR_IN[i]);
    if (valueIn[i]) {
      flagIn[i] = true;
    }
    if ((flagIn[i] == true ) && (valueIn[i] == false)) {
      for (int k = 0; k < 4; k++) {
        if (roads[k].id == i) {
          roads[k].carCount++;
          totalCars++;
          Serial.println("Road " + String(i) + " Cars " + String(roads[k].carCount));
        }
      }
      flagIn[i] = false;
    }
    // count --
    valueOut[i] = !digitalRead(CAR_OUT[i]);
    if (valueOut[i]) {
      flagOut[i] = true;
    }
    if ((flagOut[i] == true ) && (valueOut[i] == false)) {
      for (int k = 0; k < 4; k++) {
        if (roads[k].id == i) {
          if (roads[k].carCount > 0) {
            totalCars--;
            roads[k].carCount--;
            Serial.println("Road " + String(i) + " Cars " + String(roads[k].carCount));
          }
        }
      }
      flagOut[i] = false;
    }
  }

  if (timeCounter >= timeTillStuck) {
    for (int k = 0; k < 4; k++) {
      turnRed(k);
    }

    bubbleSort(roads, 4 - roadsDoneTillNow);
    struct Road currentRoad = roads[3 - roadsDoneTillNow];

    totalCars = 0;
    for (int k = 0; k < 4 - roadsDoneTillNow; k++) {
      totalCars += roads[k].carCount;
    }

    for (int k = 0; k <= 3 - roadsDoneTillNow; k++) {
      roads[k].allocatedTime = timeRemaining * (double)roads[k].carCount / (double)totalCars;
    }

    timeRemaining -= currentRoad.allocatedTime;
    timeTillStuck = timeCounter + currentRoad.allocatedTime;
    // Green Light for the max car road
    Serial.println();
    Serial.println("now road " + String(currentRoad.id) + " is on");
    if (currentRoad.allocatedTime!=0)
      turnGreen(currentRoad.id);
    roadsDoneTillNow++;

    if (roadsDoneTillNow == 4) {
      roadsDoneTillNow = 0;
      timeRemaining = CYCLE_TIME;
    }

    Serial.println("current time: " + String(timeCounter));
    for (int i = 0; i < 4; i++) {
      Serial.print("Road " + String(roads[i].id) + " Cars " + String(roads[i].carCount) + " time alot: ");
      Serial.print(roads[i].allocatedTime);
      Serial.println();
    }
  }

  delay(1);
  timeCounter += 1;
}
