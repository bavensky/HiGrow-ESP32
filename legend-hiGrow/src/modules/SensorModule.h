#include <CMMC_Module.h>

#ifndef CMMC_SensorModule_MODULE_H
#define CMMC_SensorModule_MODULE_H 

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <CMMC_Sensor.h>
#include <CMMC_Interval.h>
#include <Adafruit_BME280.h>
#include <Adafruit_ADS1015.h> 
#include "DHT.h"

const int MAX_ARRAY = 5;

// hiGrow pinout
const int DHTPIN = 22;
#define DHTTYPE DHT11
const int soilpin = 32;
const int POWER_PIN = 34;
const int LIGHT_PIN = 33;

class SensorModule: public CMMC_Module {
  public:
    void config(CMMC_System *os, AsyncWebServer* server); 
    void setup();
    void loop(); 
    void isLongPressed(); 
    void configLoop();
    String getTemperatureString();
    String getHumidityString();
    float getTemperature();
    float getHumidity();
    int getWaterLevel();
    int getLightLevel();

    int16_t adc0;
    int16_t adc1;
    int16_t adc2;
    int16_t adc3; 
  protected:
    void configWebServer();
  private:
    Adafruit_BME280 *bme;
    DHT *dht;
    CMMC_SENSOR_DATA_T data1; 
    CMMC_Interval interval;
    
    float temp_array[MAX_ARRAY] = { 0.0 };
    float humid_array[MAX_ARRAY] = { 0.0 };
    float pressure_array[MAX_ARRAY] = { 0.0 };

    float _temperature;
    float _humidity;
    float _pressure; 
    int   _waterlevel;
    int   _lightlevel;

    unsigned long counter = 0;
    Adafruit_ADS1115 *ads;
    

};

#endif