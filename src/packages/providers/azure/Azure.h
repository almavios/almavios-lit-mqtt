#ifndef __ALMAVIOS_LIT_CLOUD_PROVIDER_AZURE__
#define __ALMAVIOS_LIT_CLOUD_PROVIDER_AZURE__    
    #include "../Providers.h"

    struct LitCloudAzureApi{
        private:
            const char *iot_device_id;
            const char *iot_hub_name;
            std::string iot_hub_hostname;
            std::string iot_hub_user;
            const char *main_sub_topic;
            std::string getShieldPubTopic(const char*);
            std::string getShieldSubTopic(const char*);
            

            #ifdef ARDUINO_ARCH_ESP32
                const char* cert;
                const char* key;
                static const char* provider_cert;
            #endif
            #ifdef ARDUINO_ARCH_ESP8266
                static unsigned char provider_cert[];
                static unsigned int provider_cert_length;
                const uint8_t* cert;
                size_t cert_length;
                const uint8_t* key;
                size_t key_length;
            #endif

            void begin(const char *hub_name, const char *device_id);
        public:
            LitCloudAzureApi();
            void setConnection(LIT_WIFI_CLIENT&, PubSubClient&, MQTT_CALLBACK_SIGNATURE);
            bool connect(PubSubClient&);
            std::string getMainPubTopic();
            std::string getMainSubTopic();            

            #ifdef ARDUINO_ARCH_ESP32
                void begin(const char *hub_name, const char *device_id, const char* cert, const char* key);
            #endif
            #ifdef ARDUINO_ARCH_ESP8266
                void begin(const char *hub_name, const char *device_id, const uint8_t* cert, size_t cert_length, const uint8_t* key, size_t key_length);
            #endif
    };
#endif