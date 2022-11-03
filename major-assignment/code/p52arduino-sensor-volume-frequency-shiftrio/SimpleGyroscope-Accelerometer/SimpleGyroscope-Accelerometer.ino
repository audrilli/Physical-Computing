/*
  Arduino LSM6DS3 - Simple Gyroscope

  This example reads the gyroscope values from the LSM6DS3
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Uno WiFi Rev 2 or Arduino Nano 33 IoT

  created 10 Jul 2019
  by Riccardo Rizzo

  This example code is in the public domain.
*/

#include <Arduino_LSM6DS3.h>

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1)
      ;
  }
  //Serialprint setup Gyroscope
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");

  //Serialprint setup Accelerometer
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");
  Serial.println("X\tY\tZ");
}

void loop() {
  float xg, yg, zg;
  float xa, ya, za;

  if (IMU.gyroscopeAvailable() && IMU.accelerationAvailable()) {
    IMU.readAcceleration(xa, ya, za);    
    IMU.readGyroscope(xg, yg, zg);
    Serial.print("xg: ");
    Serial.print(xg);
    Serial.print('\t');
    Serial.print("yg: ");
    Serial.print(yg);
    Serial.print('\t');
    Serial.print("zg: ");
    Serial.print(zg);
    Serial.print('\t');
    Serial.print("xa: ");
    Serial.print(xa);
    Serial.print('\t');
    Serial.print("ya: ");
    Serial.print(ya);
    Serial.print('\t');
    Serial.print("za: ");
    Serial.println(za);


  }
}
//   float xa, ya, za;

//   if () {

//     Serial.print("xa: ");
//     Serial.print(xa);
//     Serial.print('\t');
//     Serial.print("ya: ");
//     Serial.print(ya);
//     Serial.print('\t');
//     Serial.print("za: ");
//     Serial.println(za);
//   }
// }