#include <AlmaviosLitMqtt.h>
#include "certs.h"

#define SSID_        "YourWifiSSID"
#define PASSWORD_    "writeyourpassword"
long lastMsg = 0;

void setup(){
    LitCloudAzure.begin(
        "nameofyourhub", "yourdeviceid",
        device_crt, device_crt_len,
        device_key, device_key_len
    );

    LitMqtt.begin(SSID_, PASSWORD_, LitCloudAzure);
}

void loop(){
    LitMqtt.run();

    long now = millis();
    if (now - lastMsg > 1200) {
        lastMsg = now;
        LitMqtt.publish("An important message");
    }
}