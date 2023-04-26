#include <cstdio>
#include "mqtt.h"
#include "ui.h"
#include <iostream>
#include <unistd.h> // for usleep()
using namespace std;

//COMPILE THIS CODE WITH "g++ -o subscribe mqtt_subscribe.cpp mqtt.cpp ui.cpp -lmosquittopp -ljsoncpp"

int main(int argc, char *argv[]) {

    while(1){
    // Print three terminal windows
    print_window(5, 5);
    print_window(5, 40);
    print_window(15, 25);

    // Print heading for terminal windows
    print_window_heading("Distance", 5, 7);
    print_window_heading("Compass", 5, 42);
    print_window_heading("Enter Command", 15, 27);

    printf("\033[25;0H"); // move cursor to row and column
    mqtt mqtt_obj(host_addr, port_number); //start mqtt
    usleep(100000);
    string user_input = get_user_input(18, 28);
    printf("\33[20;28H");

    };
    return 0;
}



