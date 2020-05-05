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

// FIXME Reconsider use only one publish =D
template<> void LitMqttApi::publish(const std::string &payload){
    LitMqttApi::printf(payload.c_str());
    LitMqttApi::printf(" <= Will be send\n");
    
    bool send = this->mqtt_client.publish(this->cloud_api->getMainPubTopic().c_str(), payload.c_str());
    
    if(send) LitMqttApi::printf("Ok\n");
    else LitMqttApi::printf("ERROR \n");
}

void LitMqttApi::reconnect(){
    while(!(this->mqtt_client.connected())){
        LitMqttApi::printf("\nAttempting MQTT connection\n");
        
        // Attempt to connect
        if (this->cloud_api->connect(this->mqtt_client)) {
            LitMqttApi::printf("Connected to: ");
            LitMqttApi::printf(this->cloud_api->getMainSubTopic().c_str());
            LitMqttApi::printf("\n");

            this->mqtt_client.subscribe(
                this->cloud_api->getMainSubTopic().c_str()
            );
        } else {
            char buf_[256];
            sprintf(buf_, "%d", this->mqtt_client.state());
            LitMqttApi::printf("failed, rc=");
            LitMqttApi::printf(buf_);
            LitMqttApi::printf(" try again in 1 seconds\n");
            
            char buf[256];

            // TODO allow agnostic connection
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

void LitMqttApi::syncTime(){
    this->time_client = new NTPClient(this->wifi_udp, "pool.ntp.org");

    this->time_client->begin();
    while (!(this->time_client->update())){
        this->time_client->forceUpdate();
    }

    // TODO allow agnostic connection
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

// =========================================
// TODO Move to a utils library(printf)
// =========================================
// TODO Allow multiple arguments
void LitMqttApi::printf(const char *str){
    Serial.printf(str);
}

// =========================================
// TODO Move to a utils library(to_string)
// =========================================
// TODO: https://stackoverflow.com/questions/17627331/template-specialization-for-multiple-types
template<> std::string LitMqttApi::to_string(const float &value){
    char buffer[32];
    sprintf(buffer, "%.04f", value);
    return std::string(buffer);
}

// TODO: https://stackoverflow.com/questions/17627331/template-specialization-for-multiple-types
template<> std::string LitMqttApi::to_string(const double &value){
    char buffer[64];
    sprintf(buffer, "%.04f", value);
    return std::string(buffer);
}

template<> std::string LitMqttApi::to_string<int>(const int &value){
    char buffer[16];
    sprintf(buffer, "%d", value);
    return std::string(buffer);
}

template<> std::string LitMqttApi::to_string(const std::string &value){
    return std::string(value);
}

template<> std::string LitMqttApi::to_string(const String &value){
    return std::string(value.c_str());
}

// TODO allow user to set true and false value
template<> std::string LitMqttApi::to_string(const bool &value){
    if(value) return std::string("true");
    return std::string("false");
}

