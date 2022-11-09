#include <WiFiNINA.h>
#include <MQTT.h>
#include "wifiCredentials.h"
#define Led 11
#define potMeter A0
int diameter = 0;

int value = 0;

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
int xPos = 100;
int yPos = 100;
int prevDiameter = 0;
WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  pinMode(potMeter, INPUT);
  // attempt to connect to Wifi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print("No WiFi connection");
    delay(5000);
  }

  // once you are connected :
  Serial.println("You're connected to the network");

  //start mqtt
  //change this to match your instance name
  client.begin("audrey.cloud.shiftr.io", net);
  client.onMessage(messageReceived);
  connect();
}

void loop() {
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }
  diameter = map(analogRead(potMeter), 0, 1023, 50, 300);
  if (diameter != prevDiameter) {
    client.publish("/value", "value," + String(diameter));
  }
  prevDiameter = diameter;

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();

    //make sure you add comma after the string e.x. posX,
    client.publish("/posX", "posX," + String(xPos));
    client.publish("/posY", "posY," + String(yPos));


    //you can also send the message formatted as json
    //client.publish("/pos", "{\"x\":" + String(xPos)+ ",\"y\":" + String(yPos) + "}");

    if (xPos < 500) {
      xPos += 10;
      yPos += 5;
    } else {
      xPos = 100;
      yPos = 100;
    }
  }
  //delay(value);
}

void messageReceived(String &topic, String &payload) {
  Serial.println(topic + ": " + payload);

  if (topic == "ledBlink") {
    int blinkVal = constrain(payload.toInt(), 0, 1);
    digitalWrite(Led, blinkVal);
  }

  if (topic == "brightness") { 
    analogWrite(Led, payload.toInt();)
  }
}

void connect() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("No Wifi connection...");
    delay(1000);
  }

  //change this to match your instance
  while (!client.connect("arduino", "audrey", "j8pQAkkhYzGk0K5v")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to MQTT!");
  client.subscribe("ledBlink");
}