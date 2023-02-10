#include "LIDARLite_v4LED.h"
#include <LiquidCrystal.h>
#include <Wire.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define Motor_forward         1
#define Motor_return          0
#define Motor_L_dir_pin       7
#define Motor_R_dir_pin       8
#define Motor_L_pwm_pin       9
#define Motor_R_pwm_pin       10

#define ENC_A_L 23
#define ENC_B_L 4
#define ENC_A_R 24
#define ENC_B_R 3


#define CMPS14_address 0x60
#define BEARING_Register 2 
#define TWO_BYTES  2

 int bearing;
 int nReceived;
 byte _byteHigh;
 byte _byteLow;
int location;


// initialize x and y values
int xValue = 0;
int yValue = 0;
float voltage = 0;
float voltage1 = 0;
int btn3 =3;
int btn4 = 4;


LIDARLite_v4LED myLIDAR; 

void setup()
{


      pinMode(ENC_A_L, INPUT);
      pinMode(ENC_B_L, INPUT);
      pinMode(ENC_A_R, INPUT);
      pinMode(ENC_B_R, INPUT);

      pinMode(Motor_L_dir_pin, OUTPUT);
      pinMode(Motor_R_dir_pin, OUTPUT);
      pinMode(Motor_L_pwm_pin, OUTPUT);
      pinMode(Motor_R_pwm_pin, OUTPUT);

      lcd.begin(20,4);
      Serial.begin(9600);

      attachInterrupt(digitalPinToInterrupt(btn3),left, RISING);
      attachInterrupt(digitalPinToInterrupt(btn4),right, RISING);

      Wire.begin();

      Serial.println("Qwiic LIDARLite_v4 examples");

      if (myLIDAR.begin() == false) {
        Serial.println("Device did not acknowledge! Freezing.");
        while(1);
      }
      Serial.println("LIDAR acknowledged!");
}


int xMap = 0;
int pwm_R=0;
int pwm_L=0; 
double motor_L, motor_R;
double distance;
String distance_str;

int left_count = 0;
int right_count = 0;

int distval = 0;

double count_L = 0;
double count_R = 0;

double DistancePerPulse = 0.138;
int x = 0;   

String status = "";

float newDistance;

int stop_point = 0;

int pos1 = 0;
int pos2 = 0;

void loop()   
{
           
 xMap = 0;

 xMap =(xValue)*19/1023;

 getBearing(); 

 xValue = analogRead(A8);
 Serial.print(xValue);

  // Serial.print("New distance: ");
  // Serial.print(newDistance);
  // Serial.println(" cm");


  lcd.setCursor(0, 0);
  lcd.print("Ad distance: ");
  lcd.setCursor(16, 0);
  lcd.print("        ");

  lcd.setCursor(0, 1);
  lcd.print("M distance: ");
  lcd.setCursor(16, 1);
  lcd.print("        ");

  lcd.setCursor(0, 2);
  lcd.print("Motor status: ");
  lcd.setCursor(13, 2);
  lcd.print("        ");


  delay(100); 

  int vertical = 25;
  int horisontal = 20;

  stop_point = 25;
  newDistance = myLIDAR.getDistance();

  for (int i = 1; i < 4; i++){

    newDistance = myLIDAR.getDistance();

    while (newDistance > stop_point){

      status = "RUN FW";
      lcd.setCursor(16, 0);
      lcd.print(stop_point);

      lcd.setCursor(16, 1);
      lcd.print(newDistance);

      lcd.setCursor(13, 2);
      lcd.print(status);

      digitalWrite(Motor_R_dir_pin,Motor_forward);  
      digitalWrite(Motor_L_dir_pin,Motor_forward); 

      analogWrite(Motor_L_pwm_pin, 75);
      analogWrite(Motor_R_pwm_pin, 75); 

      lcd.setCursor(16, 1);
      lcd.print(newDistance);

      newDistance = myLIDAR.getDistance();
    }

    analogWrite(Motor_L_pwm_pin, 0);
    analogWrite(Motor_R_pwm_pin, 0); 

    int loc;

   getBearing();

   loc = bearing - 90;

        digitalWrite(Motor_R_dir_pin,Motor_forward);  
        digitalWrite(Motor_L_dir_pin,Motor_forward);


        if (loc <= 360 && loc >= 0){
           do {
                analogWrite(Motor_L_pwm_pin,70);
                analogWrite(Motor_R_pwm_pin, 0);
                getBearing();
                lcd.print(loc);
                lcd.print("\n");
                lcd.print(bearing);
            }while (bearing != loc);
          } else if (loc > 360) {
            loc = loc - 360;
            do {
                analogWrite(Motor_L_pwm_pin,70);
                analogWrite(Motor_R_pwm_pin, 0);
                getBearing();    
            }while (bearing != loc);
           } else if ( loc < 0 ){
            loc = loc + 360;
            do {
                analogWrite(Motor_L_pwm_pin,70);
                analogWrite(Motor_R_pwm_pin, 0);
                getBearing();    
            }while (bearing != loc);
            }

         analogWrite(Motor_L_pwm_pin,0);
         analogWrite(Motor_R_pwm_pin, 0);

         delay(500);

    if (stop_point == 25){
      stop_point == 20;
    } else {
      stop_point == 25;
    }
  }

  analogWrite(Motor_L_pwm_pin, 0);
  analogWrite(Motor_R_pwm_pin, 0); 

  delay(10000);

             
} 

void left(){
  count_L++;
  }
void right(){
  count_R++;
  }

void turn90(){
  
}

int16_t getBearing()
{
  // Begin communication with CMPS14
  Wire.beginTransmission(CMPS14_address);

  // Tell register you want some data
  Wire.write(BEARING_Register);

  // End the transmission
  int nackCatcher = Wire.endTransmission();

  // Return if we have a connection problem 
  if(nackCatcher != 0){return 0 ;}
  
  // Request 2 bytes from CMPS14
  nReceived = Wire.requestFrom(CMPS14_address , TWO_BYTES);

  // Something has gone wrong
  if (nReceived != TWO_BYTES) return 0;

  // Read the values
  _byteHigh = Wire.read(); 
  _byteLow = Wire.read();

  // Calculate full bearing
  bearing = ((_byteHigh<<8) + _byteLow) / 10;
  
  return bearing;
}
