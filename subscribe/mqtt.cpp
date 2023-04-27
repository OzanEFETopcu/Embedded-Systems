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

    printf("\033[29;0H");
    std::string mqtt_message;

    printf("\n ================ Message Received ================ \n");
    mqtt_message = (char*) message->payload;
    printf("Message is = %s\n", mqtt_message.c_str()) ;
    printf("\033[8;9H");

    ///// Parsing /////
    int number;
    std::string json_in = mqtt_message.c_str();
    std::string parse_out;
    Json::Reader reader;
    Json::Value obj;

    if(reader.parse(json_in, obj)==true){ //check if parsing is OK

        //Check mqtt message content
        if(obj.isMember("lidar")){
            parse_out=obj["lidar"].asInt();
            printf("\033[8;9H");
            printf("%d\n", parse_out);
        }
        if(obj.isMember("compass")){
            parse_out=obj["compass"].asInt();
            printf("\033[8;44H");
            printf("%d\n", parse_out);
        }

    }else{
        printf("----------------- Error parsing JSON -----------------\n");
    };
    ///////////////////////////////////
};


////////// send MQTT message //////////
bool mqtt::send_message(std::string message)
{
    int ret = publish(NULL, out_topic, message.length(), message.c_str(),1,true);
    return(ret == MOSQ_ERR_SUCCESS);
};