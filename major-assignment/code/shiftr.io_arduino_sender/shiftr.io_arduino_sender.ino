// SHIFTR.IO
#include "WiFi.h"
#include <MQTT.h>
#include "wifiCredentials.h"
#include <ArduinoLowPower.h>

// SHIFTR.IO
char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;

unsigned long lastMillis = 0;
int ledBlink; 

// SHIFTR.IO
WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;  
String xVal;
String yVal;
// SENSOR
#include <Adafruit_LSM6DS33.h>
Adafruit_LSM6DS33 lsm6ds; // can use any LSM6DS/ISM330 family chip!
Adafruit_Sensor *lsm_temp, *lsm_accel, *lsm_gyro;

void setup() {
  Serial.begin(115200);
  
  // SHIFTR.IO
  // attempt to connect to Wifi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    WiFi.lowPowerMode();
    Serial.print("No WiFi connection");
    delay(5000);
  }
  
  // SHIFTR.IO
  // once you are connected :
  Serial.println("You're connected to the network");
  //start mqtt
  client.begin("lars-z.cloud.shiftr.io", net);
  connect();

  // SENSOR
  /*
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
*/
  Serial.println("Adafruit LSM6DS test!");
  
  if (!lsm6ds.begin_I2C()) {
    Serial.println("Failed to find LSM6DS chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("LSM6DS Found!");
  lsm_accel = lsm6ds.getAccelerometerSensor();
  lsm_accel->printSensorDetails();

  lsm_gyro = lsm6ds.getGyroSensor();
  lsm_gyro->printSensorDetails();
}

void loop() {
  // SHIFTR.IO
  client.loop();
  delay(10);

  // SHIFTR.IO
  // check if connected
  if (!client.connected()) {
    connect();
  }

  // SENSOR
  sensors_event_t accel;
  sensors_event_t gyro;
  lsm_accel->getEvent(&accel);
  lsm_gyro->getEvent(&gyro);
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("\t\tAccel X: ");
  Serial.print(accel.acceleration.x);
  Serial.print(" \tY: ");
  Serial.print(accel.acceleration.y);
  Serial.print(" \tZ: ");
  Serial.print(accel.acceleration.z);
  Serial.println(" m/s^2 ");
  /* Display the results (rotation is measured in rad/s) */
  Serial.print("\t\tGyro X: ");
  Serial.print(gyro.gyro.x);
  Serial.print(" \tY: ");
  Serial.print(gyro.gyro.y);
  Serial.print(" \tZ: ");
  Serial.print(gyro.gyro.z);
  Serial.println(" radians/s ");
  Serial.println();
  

  // SHIFTR.IO
  // publish a message roughly every second.
  if (millis() - lastMillis > 100) {
    lastMillis = millis();
    /*
    if(ledBlink == 1) {
      ledBlink = 0;
    }else {
      ledBlink = 1;
    }*/

   //client.publish("/Gyro", "{g:" + "x" + xVal + "y" + yVal + "}");
   //client.publish("/Gyro", "gx," + String(gyro.gyro.x) + "gy," +  String(gyro.gyro.y) + "gz," +  String(gyro.gyro.z)  ) ;
   //client.publish("/Accel", "ax," + String(accel.acceleration.x) + "ay," +  String(accel.acceleration.y) + "az," +  String(accel.acceleration.z)  ) ;
   client.publish("/Gyro", String(gyro.gyro.x) + "," + String(gyro.gyro.y) + "," + String(gyro.gyro.z) + "," + String(accel.acceleration.x) + "," + String(accel.acceleration.y) + "," + String(accel.acceleration.z)) ;
  }
}

// SHIFTR.IO
void connect() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("No Wifi connection...");
    //WiFi.lowPowerMode();
    delay(500);
  }
  while (!client.connect("lars", "lars-z", "h57VsZfr5qpWt1tu")) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nconnected to MQTT!");
  
}