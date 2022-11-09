#include <WiFiNINA.h>
#include <MQTT.h>
#include "wifiCredentials.h"

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
unsigned long lastMillis = 0;
int ledBlink;

WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;

#define pinPot A0
int value = 0;
int valuePotMeter;


void setup() {
  //Serial.begin(115200);
  Serial.begin(9600);

  // attempt to connect to Wifi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print("No WiFi connection");
    delay(5000);

    pinMode(pinPot, INPUT);
  }

  // once you are connected :
  Serial.println("You're connected to the network");

  //start mqtt
  client.begin("audrey.cloud.shiftr.io", net);
  connect();
}

void loop() {
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  // if (millis() - lastMillis > 1000) {
  //   lastMillis = millis();

  //   if(ledBlink == 1) {
  //     ledBlink = 0;
  //   }else {
  //     ledBlink = 1;
  //   }
  //   client.publish("/ledBlink", String(ledBlink));
  // }

  // value = analogRead(pinPot);
  // Serial.println(value);

  if (millis() - lastMillis > 10) {
    lastMillis = millis();
    value = analogRead(pinPot);
    valuePotMeter = map(value, 0, 1023, 0, 255  );
    Serial.println(value);
    client.publish("/valuePotMeter", String(valuePotMeter));
  }
}


void connect() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("No Wifi connection...");
    delay(1000);
  }

  while (!client.connect("Audrey", "audrey", "j8pQAkkhYzGk0K5v")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to MQTT!");
  client.subscribe("ledBlink");
}