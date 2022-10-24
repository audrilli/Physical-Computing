//
// Minor Assignment
//
// Physical Computing
// ZHdK
//
// Written by Lukman Aščić & Audrey Lohmann © 2022
//

// – Task
/*
  Create a Braitenberg Vehicle that responds to phenomena of some kind and performs
  some sort of action or activity in response.
*/

// – Discussion
/*
  This project is an approach to navigation in space: At the core of our approach
  is a paper arm laying from above towards the ground. Two sonic sensors, attached
  on opposite sides, detect one persons' hand.

  As the hand gets closer to fulfill the main affordance of the paper arm (to touch it),
  it moves away from the hand as an action of escape and ignorance. This movement is initiated by
  distance sensors detecting the hands distance towards the object and influencing the rotation of
  the motors accordingly.
*/


// – Libraries
#include "Adafruit_VL53L0X.h" // Distance sensor

// – Properties
// – Objects
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X(); // Distance sensors
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

// – Addresses
#define loxAddress1 0x30 // loxPin1
#define loxAddress2 0x31 // loxPin2

// – Data
VL53L0X_RangingMeasurementData_t measure1; // Measurement
VL53L0X_RangingMeasurementData_t measure2;

int prevInterval = 0; // For time constraints (5 seconds below)
int currentInterval = 0;

bool isFirstTimeRunning = true; // One-time flag
enum Direction {
  left, right
};
Direction side;

// – Pins
#define loxPin1 A1 // Sensors
#define loxPin2 A2

#define motorPinA 5 // Motor: right
#define motorPinB 6

#define motorPinC 10 // Motor: left
#define motorPinD 11


// – Lifecycle
void setup() {
  Serial.begin(115200);

  // Waits until serial port opens for native USB devices
  while (!Serial) {
    delay(1);
  }

  setOutputs();

  Serial.println(F("Shutting down pins..."));
  // Sets sensor pins to reset mode (Shutdown)
  digitalWrite(loxPin1, LOW);
  digitalWrite(loxPin2, LOW);

  Serial.println(F("Pins reset."));

  Serial.println(F("Starting.."));
  initSensors();
}

void loop() {
  

//  while (isFirstTimeRunning == true) {
//    Serial.println("HEY");
//    detectFirst();
//  }

//    while (isFirstTimeRunning == false) {
   detect();
//    }
  

  delay(100);
}


// – Methods
// Reads the measurements from the senors
void detect() {
  lox1.rangingTest(&measure1, false); // Set to 'false' for no debug data printout
  lox2.rangingTest(&measure2, false);

  // Prints reading from lox1
  Serial.print(F("lox1: "));

  // – Right state
  // The right motor (R) is activated by the first sensor (1)
  checkMeasurementWithMotor(motorPinA);

  // – Left State
  // The left motor (L) is activated by the second sensor (2)
  checkMeasurementWithMotor(motorPinC);

  Serial.println();
}

// Turns that motor if its respective sensor detects nearby hand movement
void checkMeasurementWithMotor(int motorPin) {
  VL53L0X_RangingMeasurementData_t measure = motorPin == motorPinA ? measure1 : measure2;

  // Starts counting the time
  currentInterval = millis();
  prevInterval = currentInterval;

  // ...if not out of range
  if (measure.RangeStatus != 4) {
    Serial.print(measure.RangeMilliMeter);

    // ...if hand is less than 100 units away
    if (measure.RangeMilliMeter < 100) {

      //L2, R1
      side = motorPin == motorPinA ? right : left;

      // SGITT DA NO EIN CHALLENGE. ICH MUESS BIM ERSTE MAL BESTIMME WELLES MOTOR ICH ZERST NUME IN EIN RICHTIG LAUFE UND DAS ANDERE EIFACH STILL BLIBT BEVOR ICH BEIDE ZUM LAUFE BRINGE: IN EIN RICHTIG MUESS' JA ZERSCHT

      if (side == right) {
        // Runs motor for five seconds
        while (prevInterval - currentInterval <= 2500)  {
          prevInterval = millis();
                    digitalWrite(motorPinA, LOW);
                    digitalWrite(motorPinB, HIGH);
                    digitalWrite(motorPinC, HIGH);
                    digitalWrite(motorPinD, LOW);
          Serial.println("LEFT TURNING");
        }
                digitalWrite(motorPinA, LOW);
                digitalWrite(motorPinB, LOW);
                digitalWrite(motorPinC, LOW);
                digitalWrite(motorPinD, LOW);
        Serial.println("LEFT DONE");
      } else {
        // Runs motor for five seconds
        while (prevInterval - currentInterval <= 2500)  {
          prevInterval = millis();
                    digitalWrite(motorPinA, HIGH);
                    digitalWrite(motorPinB, LOW);
                    digitalWrite(motorPinC, LOW);
                    digitalWrite(motorPinD, HIGH);
          Serial.println("RIGHT TURNING");
        }
                digitalWrite(motorPinA, LOW);
                digitalWrite(motorPinB, LOW);
                digitalWrite(motorPinC, LOW);
                digitalWrite(motorPinD, LOW);
        Serial.println("RIGHT DONE");
      }
    }
  } else {
    Serial.print(F("Out of range"));
  }
}


//void detectFirst() {
//  lox1.rangingTest(&measure1, false); // Set to 'false' for no debug data printout
//  lox2.rangingTest(&measure2, false);
//
//  // Prints reading from lox1
//  Serial.print(F("lox1: "));
//
//  // – Right state
//  // The right motor (R) is activated by the first sensor (1)
//  checkFirstMeasurementWithMotor(motorPinA);
//
//  // – Left State
//  // The left motor (L) is activated by the second sensor (2)
//  checkFirstMeasurementWithMotor(motorPinC);
//
//  Serial.println();
//}
//
//// Turns that motor if its respective sensor detects nearby hand movement
//void checkFirstMeasurementWithMotor(int motorPin) {
//  VL53L0X_RangingMeasurementData_t measure = motorPin == motorPinA ? measure1 : measure2;
//
//  // Starts counting the time
//  currentInterval = millis();
//  prevInterval = currentInterval;
//
//  // ...if not out of range
//  if (measure.RangeStatus != 4) {
//    Serial.print(measure.RangeMilliMeter);
//
//    // ...if hand is less than 100 units away
//    if (measure.RangeMilliMeter < 100) {
//
//      side = motorPin == motorPinA ? right : left;
//
//      // SGITT DA NO EIN CHALLENGE. ICH MUESS BIM ERSTE MAL BESTIMME WELLES MOTOR ICH ZERST NUME IN EIN RICHTIG LAUFE UND DAS ANDERE EIFACH STILL BLIBT BEVOR ICH BEIDE ZUM LAUFE BRINGE: IN EIN RICHTIG MUESS' JA ZERSCHT
//
//      if (side == right) {
//        // Runs motor for five seconds
//        while (prevInterval - currentInterval <= 5000)  {
//          prevInterval = millis();
//                    digitalWrite(motorPinA, LOW);
//                    digitalWrite(motorPinB, HIGH);
////                    digitalWrite(motorPinC, LOW);
////                    digitalWrite(motorPinD, LOW);
////                    isFirstTimeRunning = true;
////          Serial.println("FIRST TIME LEFT TURNING");
//        }
//                digitalWrite(motorPinA, LOW);
//                digitalWrite(motorPinB, LOW);
////                digitalWrite(motorPinC, LOW);
////                digitalWrite(motorPinD, LOW);
////        Serial.println("FIRST TIME LEFT DONE");
//        isFirstTimeRunning = false;
//      } else {
//        // Runs motor for five seconds
//        while (prevInterval - currentInterval <= 5000)  {
//          prevInterval = millis();
////                    digitalWrite(motorPinA, LOW);
////                    digitalWrite(motorPinB, LOW);
//                    digitalWrite(motorPinC, LOW);
//                    digitalWrite(motorPinD, HIGH);
////                    isFirstTimeRunning = true;
//         // Serial.println("FIRST TIME RIGHT TURNING");
//        }
////                digitalWrite(motorPinA, LOW);
////                digitalWrite(motorPinB, LOW);
//                digitalWrite(motorPinC, LOW);
//                digitalWrite(motorPinD, LOW);
//        //Serial.println("FIRST TIME RIGHT DONE");
//        isFirstTimeRunning = false;
//      }
//    }
//  } else {
//    Serial.print(F("Out of range"));
//  }
//}

// – Helpers
// Defines the pins
void setOutputs() {
  pinMode(motorPinA, OUTPUT); // Motors
  pinMode(motorPinB, OUTPUT);
  pinMode(motorPinC, OUTPUT);
  pinMode(motorPinD, OUTPUT);
  pinMode(loxPin1, OUTPUT); // Sensors
  pinMode(loxPin2, OUTPUT);
}

// Reset all sensors and initialize with their respective address (to make multiple sensors work on one Arduino)
void initSensors() {
  digitalWrite(loxPin1, LOW); // Resets all
  digitalWrite(loxPin2, LOW);
  delay(10);

  digitalWrite(loxPin1, HIGH); // Unresets all
  digitalWrite(loxPin2, HIGH);
  delay(10);

  digitalWrite(loxPin1, HIGH); // Activates lox1
  digitalWrite(loxPin2, LOW); // Resets lox2

  // Initializes lox1
  if (!lox1.begin(loxAddress1)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1);
  }
  delay(10);

  digitalWrite(loxPin2, HIGH); // Activate lox2
  delay(10);

  // Initializes lox2
  if (!lox2.begin(loxAddress2)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1);
  }
}
