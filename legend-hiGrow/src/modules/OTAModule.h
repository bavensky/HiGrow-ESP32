#include <CMMC_Module.h>

#ifndef CMMC_OTAModule_MODULE_H
#define CMMC_OTAModule_MODULE_H 

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <CMMC_Sensor.h>
#include <CMMC_Interval.h>
#include <Adafruit_BME280.h>

class OTAModule: public CMMC_Module {
  public:
    void config(CMMC_System *os, AsyncWebServer* server); 
    void setup();
    void loop(); 
    void isLongPressed(); 
    void configLoop();
  protected:
    void configWebServer();
  private:
    CMMC_Interval interval;
};

#endif