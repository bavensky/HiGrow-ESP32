#include <MqttConnector.h>
#include "DHT.h"

#define DHTPIN 22
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// hiGrow pinout
const int dhtpin = 22;
const int soilpin = 32;
const int POWER_PIN = 34;
const int LIGHT_PIN = 33;

float t, h;
int waterlevel;
int lightlevel;

#define uS_TO_S_FACTOR 1000000      /* Conversion factor for micro seconds to seconds */
uint32_t  TIME_TO_SLEEP = 10 * 60L; /* Time ESP32 will go to sleep (in seconds) */


extern int relayPinState;
extern MqttConnector *mqtt;
extern int relayPin;
extern char myName[];
extern uint32_t btCount;

static void readSensor();

extern String DEVICE_NAME;
extern int PUBLISH_EVERY;

void register_publish_hooks()
{
  strcpy(myName, DEVICE_NAME.c_str());
  mqtt->on_prepare_data_once([&](void) {
    Serial.println("initializing sensor...");
    pinMode(LIGHT_PIN, OUTPUT);
    dht.begin();
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  });

  mqtt->on_before_prepare_data([&](void) {
    readSensor();
  });

  mqtt->on_prepare_data([&](JsonObject *root) {
    JsonObject &data = (*root)["d"];
    JsonObject &info = (*root)["info"];
    data["myName"] = myName;
    data["millis"] = millis();
    data["relayState"] = relayPinState;
    data["updateInterval"] = PUBLISH_EVERY;
    data["btCount"] = btCount;

    data["waterlevel"] = waterlevel;
    data["lightlevel"] = lightlevel;

    if (isnan(h) || isnan(t))
    {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    else
    {
      data["temperature_c"] = t * 100;
      data["humidity_pervent_rh"] = h * 100;
    }

    // Serial.println("Going to sleep now");
    // esp_deep_sleep_start();
  },
                        PUBLISH_EVERY);
  mqtt->on_after_prepare_data([&](JsonObject *root) {
    /**************
      JsonObject& data = (*root)["d"];
      data.remove("version");
      data.remove("subscription");
    **************/
  });
}

static void readSensor()
{
  // perform reading sensor
  Serial.println("Perform reading sensor...");
  
  t = dht.readTemperature();
  h = dht.readHumidity();

  waterlevel = analogRead(soilpin);
  lightlevel = analogRead(LIGHT_PIN);

  waterlevel = map(waterlevel, 0, 4095, 0, 1023);
  waterlevel = constrain(waterlevel, 0, 1023);
  lightlevel = map(lightlevel, 0, 4095, 0, 1023);
  lightlevel = constrain(lightlevel, 0, 1023);

  Serial.println("===========================");
  Serial.print(t);
  Serial.print("\t");
  Serial.print(h);
  Serial.print("\t");
  Serial.print(waterlevel);
  Serial.print("\t");
  Serial.print(lightlevel);
  Serial.print("\n");
  Serial.println("===========================");
}
