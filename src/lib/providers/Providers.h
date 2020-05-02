#ifndef __ALMAVIOS_LIT_CLOUD_PROVIDERS__
#define __ALMAVIOS_LIT_CLOUD_PROVIDERS__
    #include <string>
    #ifndef PubSubClient_h
    #include "../../vendor/pubsubclient/PubSubClient.h"
    #endif
    #ifdef ARDUINO_ARCH_ESP32
        #include "WiFi.h"
    #endif
    #ifdef ARDUINO_ARCH_ESP8266
        #include <ESP8266WiFi.h>
    #endif


    struct LitCloudAzureApi{
        private:
            static unsigned char provider_cert[];
            static unsigned int provider_cert_length;
            const uint8_t* cert;
            size_t cert_length;
            const uint8_t* key;
            size_t key_length;
            const char *iot_device_id;
            const char *iot_hub_name;
            std::string iot_hub_hostname;
            std::string iot_hub_user;
            const char *main_sub_topic;
            std::string getShieldPubTopic(const char*);
            std::string getShieldSubTopic(const char*);
        public:
            LitCloudAzureApi();
            void begin(const char *hub_name, const char *device_id);
            void begin(const char *hub_name, const char *device_id, const uint8_t* cert, size_t cert_length, const uint8_t* key, size_t key_length);
            void setConnection(WiFiClientSecure&, PubSubClient&, MQTT_CALLBACK_SIGNATURE);
            bool connect(PubSubClient&);
            std::string getMainPubTopic();
            std::string getMainSubTopic();            
    };

#endif