#include "AlmaviosLitMqttApi.h"

LitMqttApi::LitMqttApi(){}

void LitMqttApi::begin(const char* ssid, const char* password, LitCloudAzureApi &cloud_api){
    this->ssid = ssid;
    this->password = password;
    this->cloud_api = &cloud_api; //Reference to the same element
    this->connectWifi(this->ssid, this->password);
    this->syncTime();
    this->cloud_api->setConnection(this->esp_client, this->mqtt_client, &LitMqttApi::callback);
}

void LitMqttApi::connectWifi(const char* ssid, const char* password){
    int status = WiFi.status();
    
    // check for the presence of the shield:
    if (status == WL_NO_SHIELD) {
        this->printf("WiFi module not found\n");
    }

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        this->printf(".");
    }
    
}

void LitMqttApi::reconnect(){
    while(!(this->mqtt_client.connected())){
        LitMqttApi::printf("Attempting MQTT connection\n");

        // Attempt to connect
        if (this->cloud_api->connect(this->mqtt_client)) {
            LitMqttApi::printf("Connected to: ");
            LitMqttApi::printf(this->cloud_api->getMainSubTopic().c_str());
            LitMqttApi::printf("\n");

            this->mqtt_client.subscribe(
                this->cloud_api->getMainSubTopic().c_str()
            );
        } else {
            char *tmp;
            sprintf(tmp, "%d", this->mqtt_client.state());

            LitMqttApi::printf("failed, rc=");
            LitMqttApi::printf(tmp);
            LitMqttApi::printf(" try again in 1 seconds\n");
            
            char buf[256];

            #ifdef ARDUINO_ARCH_ESP32
                this->esp_client.lastError(buf,256);
            #endif
            #ifdef ARDUINO_ARCH_ESP8266
                this->esp_client.getLastSSLError(buf,256);
            #endif
            
            LitMqttApi::printf("WiFiClientSecure SSL error: ");
            LitMqttApi::printf(buf);
            LitMqttApi::printf("\n");
            delay(1000);
        }
    }
}

void LitMqttApi::run(){
    if (!this->mqtt_client.connected()) this->reconnect();
    this->mqtt_client.loop();
}


void LitMqttApi::publish(const char *payload){
    this->mqtt_client.publish(this->cloud_api->getMainPubTopic().c_str(), payload);
}


void LitMqttApi::syncTime(){
    this->time_client = new NTPClient(this->wifi_udp, "pool.ntp.org");

    this->time_client->begin();
    while (!(this->time_client->update())){
        this->time_client->forceUpdate();
    }


    // #ifdef ARDUINO_ARCH_ESP32
    // #endif
    #ifdef ARDUINO_ARCH_ESP8266
        this->esp_client.setBufferSizes(512, 512);
        this->esp_client.setX509Time(this->time_client->getEpochTime());
    #endif
}

void LitMqttApi::callback(char* topic, byte* payload, unsigned int length){
    LitMqttApi::printf("Message arrived [");
    LitMqttApi::printf(topic);
    LitMqttApi::printf("] ");
    for (int i = 0; i < length; i++)
        LitMqttApi::printf((char *)payload[i]);

    LitMqttApi::printf("\n");
}


void LitMqttApi::printf(const char *str){
    Serial.printf(str);
}