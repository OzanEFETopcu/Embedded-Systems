#ifndef MQTT_H
#define MQTT_H

#include <mosquitto.h>
#include <mosquittopp.h>

#define in_topic "EMB2_in"
#define out_topic "EMB2_out"
#define host_addr "172.28.16.138"
#define port_number 1883
#define client_id "ict_2020_zx"


class mqtt : public mosqpp::mosquittopp
{
    public:
        mqtt(const char *host, int port); // Add parameter declaration
        ~mqtt(){};

        void on_connect(int rc);
        void on_message(const struct mosquitto_message *message);
        void on_subscribe(int mid, int qos_count, const int *granted_qos);
};

#endif // MQTT_H