# AlmaviosLitMqtt
A simple arduino library provisioning a client to connect with Cloud Providers, via MQTT. It is looking for agnostic connection. 

This library is based on other amazing projects, for MQTT connection [PubSubClient](https://github.com/knolleary/pubsubclient) is included. The connection should be secured with your cloud providers, to get current time [NTPClient](https://github.com/arduino-libraries/NTPClient) is also included.

## Content
* [Content](#content)
* [Examples](#examples)
  * [Specific container setup](#specific-container-setup)
    * [ESP8266](#esp8266)
    * [ESP32](#esp32)
  * [Agnostic examples](#agnostic-examples)
    * [Basic publish](#basic-publish)
    * [CSV publish](#csv-publish)
* [License](#license)

## Examples

You must include `AlmaviosLitMqtt.h` to use the library, the below code is the representation of a basic connection with Azure. This example uses x.509 as authentication, so you must have a cert and key file.

The CN of the certification will be the same of your IoT device. The CA cert must be in the Azure hub, otherwise the connection will be refused. In future versions, we will allow SAS connection. Your cert and key file must be provided to `LitCloudProvider`, we recommend for development **openssl** to get it in binary form.

### Specific container setup

Nowadays, `AlmaviosLitMqtt` have a basic support using arduino of ESP32 and ESP8266. This project aims agnostic connection to cloud providers, but to be almost play-and-plug we are trying to reduce the over configuration for each supported `container`(board). 

#### ESP8266

An example using ESP8266 with Arduino, version 2.5.2 of the boards. The certs will be in binary form

```C++
#include <AlmaviosLitMqtt.h>
#include "certs.h"

#define SSID_        "YourWifiSSID"
#define PASSWORD_    "writeyourpassword"

void setup(){
    Serial.begin(115200);

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

#### ESP32

An example using ESP32 with Arduino, version 1.0.4 of the boards. The certs will be `const char*`

```C++
#include <AlmaviosLitMqtt.h>
#include "certs.h"

#define SSID_        "YourWifiSSID"
#define PASSWORD_    "writeyourpassword"

void setup(){
    Serial.begin(115200);
    LitCloudAzure.begin( "nameofyourhub", "yourdeviceid", device_crt, device_key);
    LitMqtt.begin(SSID_, PASSWORD_, LitCloudAzure);
}

void loop(){
    LitMqtt.run();
    // ...
    LitMqtt.publish("An important message");
}
```

### Agnostic examples

All the examples show below, are using the same parent structure. It does not matter the cloud provider or container you are using, the code will be the same. For simplicity, the snippets are from the sendMsg() function.

As you can see in the below code, Azure provider is being used, you can replace it without a problem in the setup. 

```C++
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
    // {{ The magic occurs here }}
}

void loop(){
    LitMqtt.run();   

    long now = millis();
    if (now - lastMsg > 16000) {
        lastMsg = now;
        sendMsg();
    }
} 
```

#### Basic publish

All the magic is inside the publish common method. The default topic, you can not change it yet, is in the form asked by your provider. Therefore, your code will be easier to read and you can focus on other important things. Nowadays the support types are `String`, `std::string`, `int`, `float`, `double` and `boolean`. 

```C++
LitMqtt.publish(555);
// Or
LitMqtt.publish("555");
```

The boolean output will be *true* and *false*. All the data is parsed to ASCII characters, we are still working to handle it in binary form; it is important if you are looking to reduce the weight of each message. 

#### CSV publish

If you are looking to send multiple attributes, you can format your data manually. LitMqtt helps you with a simple format **CSV**. In this format, the values are separeted by commas. You can reach this format using an array and our helper method `publishCSV()`. For this publisher, you have two options, create the array **outside** the method or be **explicit** with the method.

The external path, you can create an array with the supported types(the same as publish)
```C++
float values[] = {speed, 30.2, ..., light};
LitMqtt.publishCSV(values);
```

The next option, avoid the creation of a variable, but you need to write the datatype and the array length. 

```C++
LitMqtt.publishCSV<bool,4>({0, 4, false, true});
```

If the length does not correspond with the written number, an error can be throw be the IDE.

## License
[Mozilla Public License v2.0](https://github.com/almavios/almavios-lit-mqtt/blob/master/LICENSE)