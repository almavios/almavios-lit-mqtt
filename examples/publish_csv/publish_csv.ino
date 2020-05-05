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

    // ======== Basic ========
    //LitMqtt.publish(555);

    // ======== External ========
    float values[] = {temperature, humidity, atm_preassure, light};
    LitMqtt.publishCSV(values);
    
    //String values[] = {"first string", "second string", "third string"};
    //LitMqtt.publishCSV(values);
    
    // ======== Explicit ========
    //LitMqtt.publishCSV<int,4>({temperature, humidity, atm_preassure, light});
    //LitMqtt.publishCSV<bool,8>({34, 60, 90, 100, 200, false, true});
}


void loop(){
    LitMqtt.run();   

    long now = millis();
    if (now - lastMsg > 16000) {
        lastMsg = now;
        sendMsg();
    }
  
} 