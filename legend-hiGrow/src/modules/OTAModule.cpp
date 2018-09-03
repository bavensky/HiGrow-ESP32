#include "OTAModule.h"
#include "LCDModule.h"


extern LCDModule* lcdModule;

void OTAModule::configLoop() {
}

void OTAModule::config(CMMC_System *os, AsyncWebServer *server)
{
  if (lcdModule) {
    // lcdModule->displayConfigWiFi(); 
  }
}

void OTAModule::configWebServer()
{
  static OTAModule *that = this;
}

void OTAModule::setup()
{
}

void OTAModule::loop() 
{ 
  interval.every_ms(5000, [&]() { });
}
