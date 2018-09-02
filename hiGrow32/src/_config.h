#include <Arduino.h> 

/* BOARD INFO */
String DEVICE_NAME      = "hiGrow-001"; 

/* WIFI INFO */ 
// String WIFI_SSID        = "ampere";
// String WIFI_PASSWORD    = "espertap";
String WIFI_SSID        = "T123456";
String WIFI_PASSWORD    = "V4bTaMaTo";

/* MQTT INFO */ 
String MQTT_HOST        = "mqtt.cmmc.io";
String MQTT_USERNAME    = "";
String MQTT_PASSWORD    = "";
String MQTT_CLIENT_ID   = "";
String MQTT_PREFIX      = "/hiGrow";
int    MQTT_PORT        = 1883;
int PUBLISH_EVERY       = 5L * 1000;
int MQTT_CONNECT_TIMEOUT= 120; 


/*
* board
*   mosquitto_sub -t "/KIDBRIGHT/gearname/#" -h gb.netpie.io -i su0QpRQr07EPm9oi -u "j4RZnUdLQLEZOqR" -P "Ztt2Ec8TLm6EXGQyWnRkv2aueLE=" -p 1883 -d
* subscribe
*   mosquitto_sub -t "/KIDBRIGHT/gearname/#" -h gb.netpie.io -i eWkn1mOvYkF8Ch45 -u "G6IXOuls4EtZcBI" -P "gXHzHsfnsUFvfx598jUm49utfqY=" -p 1883 -d
* web
*   mosquitto_sub -t "/KIDBRIGHT/gearname/#" -h gb.netpie.io -i PojWnKM8EBWV6XbC -u "G6IXOuls4EtZcBI" -P "Sij29iKaTU3sDM9k+25vreNkw5w=" -p 1883 -d
*/