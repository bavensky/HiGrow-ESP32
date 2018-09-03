#include "NTPModule.h"
#include "logo.h"

void NTPModule::configLoop() {

}

void NTPModule::config(CMMC_System *os, AsyncWebServer *server) {
}

void NTPModule::configWebServer()
{
  static NTPModule *that = this;
} 

void NTPModule::setup() {
  udp.begin(localPort);
}

void NTPModule::loop() {
  interval.every_ms(500, [&]() {
    WiFi.hostByName(ntpServerName, timeServerIP);
    sendNTPpacket(timeServerIP); // send an NTP packet to a time server
    int cb = udp.parsePacket();
    if (!cb) {
      Serial.println("no packet yet");
    }
    else {
      udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer 
      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
      unsigned long secsSince1900 = highWord << 16 | lowWord;
      const unsigned long seventyYears = 2208988800UL;
      epoch = secsSince1900 - seventyYears; 
      unix = epoch; 
      lastUpdateMs = millis();
    }
  });

  interval2.every_ms(1000, [&]() {
    printTime(); 
  });
}

void NTPModule::printTime() {
      // print the hour, minute and second:
    unsigned long _epoch = epoch+25200;
    Serial.print("The GMT+7 time is ");       // UTC is the time at Greenwich Meridian (GMT)
    Serial.print((_epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if ( ((_epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((_epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ( (_epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print(_epoch % 60); // print the second
    Serial.printf(" (%lu) delta=%lums\r\n", _epoch-25200, millis() - lastUpdateMs); 
}


// send an NTP request to the time server at the given address
void NTPModule::sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

String NTPModule::getTimeString() {
  String timeString = "";
  unsigned long _epoch = epoch+25200;
  timeString += ((_epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
  timeString += (':');
  if ( ((_epoch % 3600) / 60) < 10 ) {
    timeString+=('0');
  }
  timeString+= ((_epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
  timeString+= (':');
  if ( (_epoch % 60) < 10 ) {
    // In the first 10 seconds of each minute, we'll want a leading '0'
    timeString+= ('0');
  }
  timeString+=(_epoch % 60); // print the second
  return timeString;
}