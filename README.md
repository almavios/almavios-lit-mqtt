# AlmaviosLitMqtt
A simple arduino library provisioning a client to connect with Cloud Providers, via MQTT. It is looking for agnostic connection. 

This library is based on other amazing projects, for MQTT connection [PubSubClient](https://github.com/knolleary/pubsubclient) is included. The connection should be secured with your cloud providers, to get current time [NTPClient](https://github.com/arduino-libraries/NTPClient) is also included.

## Content
* [Content](#content)
* [Examples](#examples)
  * [ESP8266](#esp8266)
  * [ESP32](#esp32)
* [License](#license)

## Examples

You must include `AlmaviosLitMqtt.h` to use the library, the below code is the representation of a basic connection with Azure. This example uses x.509 as authentication, so you must have a cert and key file.

The CN of the certification will be the same of your IoT device. The CA cert must be in the Azure hub, otherwise the connection will be refused. In future versions, we will allow SAS connection. Your cert and key file must be provided to `LitCloudProvider`, we recommend for development **openssl** to get it in binary form.

### ESP8266

An example using ESP8266 with Arduino, version 2.5.2 of the boards. The certs will be in binary form

```C++
#include <AlmaviosLitMqtt.h>
#include "certs.h"

#define SSID_        "YourWifiSSID"
#define PASSWORD_    "writeyourpassword"

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
    // ...
    LitMqtt.publish("An important message");
}
```

### ESP32

An example using ESP32 with Arduino, version 1.0.4 of the boards. The certs will be `const char*`

```C++
#include <AlmaviosLitMqtt.h>
#include "certs.h"

#define SSID_        "YourWifiSSID"
#define PASSWORD_    "writeyourpassword"

void setup(){
    LitCloudAzure.begin( "nameofyourhub", "yourdeviceid", device_crt, device_key);
    LitMqtt.begin(SSID_, PASSWORD_, LitCloudAzure);
}

void loop(){
    LitMqtt.run();
    // ...
    LitMqtt.publish("An important message");
}
```


## License
[Mozilla Public License v2.0](https://github.com/almavios/almavios-lit-mqtt/blob/master/LICENSE)