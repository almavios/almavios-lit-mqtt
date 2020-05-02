/*
    Author:      Antonio Perez (antonio@almavios.com)
    Description: Connect ESP8266 to Azure via MQTT over TLS/SSL, this version uses x.509 

    Note[1]:     Provide to setCACert() DigiCert Baltimore Root Certificate. Use openssl to get it in the correct form.
        Note[a]:    https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-mqtt-support#tlsssl-configuration
        Note[b]:    https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c
    Note[2]:     Use ntpUDP to setX509Time(). If it is not provided, an SSL error will be throw.
    Note[3]:     The esp8266 cert and key must have in the CN your device ID, it must be signed by a CA allowed in your IoT Hub.
        Note[a]:    https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-x509ca-overview#sign-devices-into-the-certificate-chain-of-trust
        Note[b]:    https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-security-x509-get-started
    Note[4]:     To debug MQTT error codes https://pubsubclient.knolleary.net/api.html#state
    Note[5]:     This file is the result of Open-source, blog contributions, documentations, and the questions of many users:
        Note[a]:    https://raphberube.com/blog/2019/02/18/Making-the-ESP8266-work-with-AWS-IoT.html
        Note[b]:    https://github.com/copercini/esp8266-aws_iot/issues/14#issuecomment-463197348
        Note[c]:    https://www.espressif.com/sites/default/files/documentation/5a-esp8266_sdk_ssl_user_manual_en.pdf
        Note[d]:    https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-secure-class.html#setcertificate
        Note[e]:    https://nofurtherquestions.wordpress.com/2016/03/14/making-an-esp8266-web-accessible#post-178 
        Note[f]:    http://www.radupascal.com/2016/04/03/esp8266-arduino-iot-hub
        Note[g]:    https://www.digitalocean.com/community/tutorials/openssl-essentials-working-with-ssl-certificates-private-keys-and-csrs
    Disclaimer:  This version works with ESP8266(Board 2.5.2), CPU 160Mhz. This version has a test cert, change to yours. It will be removed in future releases
*/
#ifndef __ALMAVIOS_LIT_MQTT__
#define __ALMAVIOS_LIT_MQTT__
    #include "AlmaviosLitMqttApi.h"

    LitMqttApi LitMqtt;
    LitCloudAzureApi LitCloudAzure;
#endif