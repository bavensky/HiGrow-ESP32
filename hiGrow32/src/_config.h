#include <Arduino.h> 

/* BOARD INFO */
String DEVICE_NAME      = "KB-001"; 

/* WIFI INFO */ 
String WIFI_SSID        = "ampere";
String WIFI_PASSWORD    = "espertap";

/* MQTT INFO */ 
String MQTT_HOST        = "gb.netpie.io";
String MQTT_USERNAME    = "j4RZnUdLQLEZOqR";
String MQTT_PASSWORD    = "Ztt2Ec8TLm6EXGQyWnRkv2aueLE=";
String MQTT_CLIENT_ID   = "su0QpRQr07EPm9oi";
String MQTT_PREFIX      = "/KIDBRIGHT/gearname";
int    MQTT_PORT        = 1883;
int PUBLISH_EVERY       = 30L * 1000;
int MQTT_CONNECT_TIMEOUT= 120; 


/*
* board
*   mosquitto_sub -t "/KIDBRIGHT/gearname/#" -h gb.netpie.io -i su0QpRQr07EPm9oi -u "j4RZnUdLQLEZOqR" -P "Ztt2Ec8TLm6EXGQyWnRkv2aueLE=" -p 1883 -d
* subscribe
*   mosquitto_sub -t "/KIDBRIGHT/gearname/#" -h gb.netpie.io -i eWkn1mOvYkF8Ch45 -u "G6IXOuls4EtZcBI" -P "gXHzHsfnsUFvfx598jUm49utfqY=" -p 1883 -d
* web
*   mosquitto_sub -t "/KIDBRIGHT/gearname/#" -h gb.netpie.io -i PojWnKM8EBWV6XbC -u "G6IXOuls4EtZcBI" -P "Sij29iKaTU3sDM9k+25vreNkw5w=" -p 1883 -d
*/