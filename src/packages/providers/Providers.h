#ifndef __ALMAVIOS_LIT_CLOUD_PROVIDERS__
#define __ALMAVIOS_LIT_CLOUD_PROVIDERS__
    #include <string>
    #ifndef PubSubClient_h
    #include "../../vendor/pubsubclient/PubSubClient.h"
    #endif
    #ifdef ARDUINO_ARCH_ESP32
        #include "WiFi.h"
        #include <WiFiClientSecure.h>
        #define LIT_WIFI_CLIENT WiFiClientSecure
    #endif
    #ifdef ARDUINO_ARCH_ESP8266
        #include <ESP8266WiFi.h>
        #define LIT_WIFI_CLIENT WiFiClientSecure
    #endif
  
    // *************** Include different providers ******************
    #include "azure/Azure.h"
#endif