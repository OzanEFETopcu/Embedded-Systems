#include <cstdio>
#include <string>
#include <jsoncpp/json/json.h>

int main(int argc, char *argv[]){

    printf("Raspberry Pi MQTT receive demo\n");
    printf("\n  JSON test\n");

    std::string json_in = argv[1];

    std::string parse_out;

    int number;

    Json::Reader reader;
    Json::Value obj;

    printf("\n String to parse = %s\n", json_in.c_str());

    if(reader.parse(json_in, obj)==true){ //check if parsing is OK

        //Check mqtt message content
        // is there string value in car tag in message //

        if(obj["TFL"]==1){
            parse_out=obj["car"].asInt();
            printf(" RED\n");
        }
        if(obj["TFL"]==2){
            parse_out=obj["car"].asInt();
            printf(" YELLOW\n");
        }
        if(obj["TFL"]==3){
            parse_out=obj["car"].asInt();
            printf(" GREEN\n");
        }

    }else{
        printf("----------------- Error parsing JSON -----------------\n");
    };


    return 0;
}
