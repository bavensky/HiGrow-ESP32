#include <CMMC_Legend.h>
#include <CMMC_Sensor.h>

#include "modules/LCDModule.h"
#include "modules/NTPModule.h"
#include "modules/WiFiModule.h"
#include "modules/MqttModule.h"
#include "modules/SensorModule.h"

const char* MEOBOT_VERSION = "1.3";

CMMC_Legend os; 
LCDModule *lcdModule;
NTPModule *ntpModule;
SensorModule *sensorModule;
WiFiModule* wifiModule;


void setup()
{ 
  lcdModule = new LCDModule();
  wifiModule = new WiFiModule();
  ntpModule = new NTPModule();
  sensorModule = new SensorModule();

  os.addModule(sensorModule);
  os.addModule(lcdModule); 
  os.addModule(wifiModule); 
  os.addModule(ntpModule); 
  os.addModule(new MqttModule()); 

  os.setup();
  Serial.printf("APP VERSION: %s\r\n", LEGEND_APP_VERSION);
  Serial.printf("MEOBOT VERSION: %s\r\n", MEOBOT_VERSION);
}

void loop()
{
  os.run();
}