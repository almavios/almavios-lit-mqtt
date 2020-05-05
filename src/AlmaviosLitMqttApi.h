#ifndef __ALMAVIOS_LIT_MQTT_API__
#define __ALMAVIOS_LIT_MQTT_API__
    #ifndef MQTT_MAX_PACKET_SIZE
        #define MQTT_MAX_PACKET_SIZE 256
    #endif
    #ifndef MQTT_KEEPALIVE
        #define MQTT_KEEPALIVE 60
    #endif
    
    #include "Arduino.h"
    #include <cstdarg>

    #ifdef ARDUINO_ARCH_ESP32
        #include "WiFi.h"
    #endif
    #ifdef ARDUINO_ARCH_ESP8266
        #include <ESP8266WiFi.h>
    #endif

    #include <WiFiUdp.h>
    #include "vendor/pubsubclient/PubSubClient.h"
    #include "vendor/NTPClient/NTPClient.h"

    #ifndef __ALMAVIOS_LIT_CLOUD_PROVIDERS__
        #include "packages/providers/Providers.h"
    #endif

    struct LitMqttApi{
        private:
            WiFiUDP             wifi_udp;
            NTPClient           *time_client;
            PubSubClient        mqtt_client;
            LIT_WIFI_CLIENT     esp_client;
            LitCloudAzureApi    *cloud_api;
            const char          *password;
            const char          *ssid;
            void reconnect();
            void syncTime();

            template<typename T> static std::string to_string(const T &value);
        public:
            LitMqttApi();
            void begin(const char* ssid, const char* password);
            void begin(const char* ssid, const char* password, LitCloudAzureApi &cloud_api);    
            void connectWifi(const char *ssid, const char *password);
            void run();            
            static void callback(char* topic, byte* payload, unsigned int length);
            static void printf(const char *str);
            template<typename T> void publish(const T &payload);
            template<typename T, size_t size> void publishCSV(const T (&attributes)[size]);
    };

    #include "AlmaviosLitMqttApi.ipp"
#endif