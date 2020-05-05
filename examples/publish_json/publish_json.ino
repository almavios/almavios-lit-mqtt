#include <AlmaviosLitMqtt.h>
#include "certs.h"

#define SSID_        "YourWifiSSID"
#define PASSWORD_    "writeyourpassword"
long lastMsg = 0;


void setup(){
    // Feel free to setup your cloud provider
    Serial.begin(115200);
    LitCloudAzure.begin( "nameofyourhub", "yourdeviceid", device_crt, device_key);
    LitMqtt.begin(SSID_, PASSWORD_, LitCloudAzure);
}

void sendMsg(){
    float temperature = 25 + random(10)/4.0;
    float humidity = random(10)/4.0;
    float atm_preassure = random(200)/2000.0;
    float light = random(4000, 40000);

    // ======== JSON External ========
    float values[] = {temperature, humidity, atm_preassure, light, 50.34};
    String keys[] = {"temperature", "humidity", "atm_preassure", "light", "other"};
    LitMqtt.publishJSON(values, keys);

    // ======== JSON Explicit ========
    // LitMqtt.publishJSON<float, String, 5>({temperature, humidity, atm_preassure, light, 50.34}, {"temperature", "humidity", "atm_preassure", "light", "other"});
}


void loop(){
    LitMqtt.run();   

    long now = millis();
    if (now - lastMsg > 16000) {
        lastMsg = now;
        sendMsg();
    }
  
} 