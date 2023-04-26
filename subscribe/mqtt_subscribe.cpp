#include <cstdio>
#include "mqtt.h"

//COMPILE THIS CODE WITH "g++ -o subscribe mqtt_subscribe.cpp mqtt.cpp -lmosquittopp -ljsoncpp"

int main(int argc, char *argv[]) {

    printf("Raspberry Pi MQTT receive demo\n");
    printf("\n  Subscribed to listen MQTT messages  \n");

    mqtt mqtt_obj(host_addr, port_number); //start mqtt

    while(1);
    return 0;
}



