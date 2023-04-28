#ifndef MQTT_H
#define MQTT_H

#include <mosquitto.h>
#include <mosquittopp.h>
#include <string>

#define in_topic "topic_receive"
#define out_topic "topic_send"
#define host_addr "10.6.0.24"
#define port_number 1883
#define client_id "ict_2020_zx"


class mqtt : public mosqpp::mosquittopp
{
    public:
        mqtt(const char *host, int port); // Add parameter declaration
        ~mqtt(){};

        void on_connect(int rc);
        //void on_message(const struct mosquitto_message *message);
        void on_subscribe(int mid, int qos_count, const int *granted_qos);
        bool send_message(std::string message);
};

#endif // MQTT_H