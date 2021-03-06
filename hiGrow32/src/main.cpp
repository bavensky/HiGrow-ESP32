#include <Arduino.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <ArduinoJson.h>
#include <MqttConnector.h>
#include <Wire.h>
#include <SPI.h>

#include "init_mqtt.h"
#include "_publish.h"
#include "_receive.h"
#include "_config.h"

MqttConnector *mqtt;

int relayPin = 26;
int relayPinState = HIGH;
char myName[40];
int x, y;
uint32_t btCount = 0;
uint8_t led;

uint64_t chipid;
char deviceid[21];

void init_hardware()
{
  pinMode(relayPin, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(relayPin, relayPinState);

  // serial port initialization
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("Starting...");
  chipid = ESP.getEfuseMac();
  sprintf(deviceid, "%" PRIu64, chipid);
  Serial.print("DeviceId: ");
  Serial.println(deviceid);
}

void init_wifi()
{
  WiFi.disconnect();
  delay(20);
  WiFi.mode(WIFI_STA);
  delay(50);
  const char *ssid = WIFI_SSID.c_str();
  const char *pass = WIFI_PASSWORD.c_str();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.printf("Connecting to %s:%s\r\n", ssid, pass);
    delay(300);
  }
  Serial.println("WiFi Connected.");
  digitalWrite(33, HIGH);
}

void setup()
{
  init_hardware();
  init_wifi();
  init_mqtt();
}

uint32_t preTime = 0;

void loop()
{
  // //    sync_advpub("prefix", "topic", "payload", "retain")
  // mqtt->sync_advpub("", "/KIDBRIGHT/gearname/kb", String(btCount), false);
  uint32_t curTime = millis();
  if (curTime - preTime >= (6*1000))
  {
    Serial.println("Going to sleep now");
    esp_deep_sleep_start();
    preTime = curTime;
  }
  mqtt->loop();
}