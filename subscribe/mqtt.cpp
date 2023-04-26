#include "mqtt.h"
#include <cstdio>
#include <string>
#include <mosquitto.h>
#include <mosquittopp.h>
#include <jsoncpp/json/json.h>

mqtt::mqtt(const char *host, int port){
    int keepalive = 60;
    printf("*****   MQTT CONNECTING...  *****\n");
    connect(host, port, (int) keepalive);
    loop_start();
};


////////////////  ON CONNECT ////////////////
void mqtt::on_connect(int rc){
    printf("*****   MQTT CONNECTED with code= %d  *****\n", rc);
    if(rc == 0){
        /*  Only attempt to subscribe on a successful connection  */
        subscribe(NULL, in_topic);
        printf("*****   SUBSCRIBED to topic= %s  *****\n", in_topic);
    };
};


////////////////  ON SUBSCRIBE  ////////////////
void mqtt::on_subscribe(int mid, int qos_count, const int *granted_qos){
    printf("*****   MQTT Topic subscription succeeded.  *****\n");
};

////////////////  ON MESSAGE  ////////////////
void mqtt::on_message(const struct mosquitto_message *message){

    std::string mqtt_message;

    printf("\n ================ Message Received ================ \n");
    mqtt_message = (char*) message->payload;
    printf("Message is = %s\n", mqtt_message.c_str()) ;

    ///// Parsing /////
    std::string json_in = mqtt_message.c_str();
    std::string parse_out;
    int number;
    Json::Reader reader;
    Json::Value obj;

    if(reader.parse(json_in, obj)==true){ //check if parsing is OK

        //Check mqtt message content
        // is there string value in car tag in message //

        if(obj["TFL"]==1){
            parse_out=obj["TFL"].asInt();
            printf(" RED\n");
        }
        if(obj["TFL"]==2){
            parse_out=obj["TFL"].asInt();
            printf(" YELLOW\n");
        }
        if(obj["TFL"]==3){
            parse_out=obj["TFL"].asInt();
            printf(" GREEN\n");
        }

    }else{
        printf("----------------- Error parsing JSON -----------------\n");
    };
    ///////////////////////////////////
};