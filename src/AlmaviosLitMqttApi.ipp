// IMPORTANT: Only template methods, for specialization methods, write them in cpp file
//            Do not forget to implement its header in this file;
#include "AlmaviosLitMqttApi.h"

// ========================================
//             Publish Section
// ========================================
template<typename T> void LitMqttApi::publish(const T &payload){
    std::string parsed_payload = LitMqttApi::to_string<T>(payload);
    this->publish(parsed_payload);
}

template<> void LitMqttApi::publish(const std::string &payload);


template<typename T, size_t size> void LitMqttApi::publishCSV(const T (&attributes)[size]){
    std::string message = "";
    
    for(T element : attributes) message += LitMqttApi::to_string(element) + ",";
    message.pop_back();

    this->publish(message);
}


// ========================================
// TODO Move to a utils library(to_string)
// ========================================
template<typename T> std::string LitMqttApi::to_string(const T &value){
    return std::string("NOT SUPPORTED DATATYPE <4>");
}

template<> std::string LitMqttApi::to_string(const int &value);
template<> std::string LitMqttApi::to_string(const float &value);
template<> std::string LitMqttApi::to_string(const double &value);
template<> std::string LitMqttApi::to_string(const int &value);
template<> std::string LitMqttApi::to_string(const std::string &value);
template<> std::string LitMqttApi::to_string(const String &value);
template<> std::string LitMqttApi::to_string(const bool &value);