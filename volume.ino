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
int num = 0; 

int lenght = 0;
int width = 0;
int height = 0;
int volume;

float newDistance;
void loop()   
{

   while (num < 6) {
       
            
 xMap = 0;
 xValue = analogRead(A8);
 yValue = analogRead(A9);

 xMap =(xValue)*19/1023;

 getBearing();


  newDistance = myLIDAR.getDistance();
  

  Serial.print("New distance: ");
  Serial.print(newDistance);
  Serial.println(" cm");

  delay(100); 

  if (num == 0 || num == 2){

    lenght += newDistance;

  } else if (num == 1 || num == 3){

    width += newDistance;
    
  } else if (num == 4 || num == 5){
    height += newDistance;
  }

  int loc = bearing + 90;

  if (loc <= 360 && loc >= 0){
    do {
        analogWrite(Motor_L_pwm_pin,70);
        analogWrite(Motor_R_pwm_pin, 0); 
        Serial.print("Bearing: ");
        Serial.print(" ");
        Serial.print(bearing);
        Serial.print("\n");
        Serial.print("loc: ");
        Serial.print(" ");
        Serial.print(loc);
        getBearing();
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

  analogWrite(Motor_L_pwm_pin, 0);
  analogWrite(Motor_R_pwm_pin, 0); 


  int value = (newDistance-20)/3;

  if (value < 0){
    value = 0;
  } else if (value > 80){
    value = 20;
  }


  lcd.setCursor(3, 0);
  lcd.print("Distance ");

  lcd.setCursor(0, 1);
  lcd.print("                   ");

  lcd.setCursor(value, 1);
  lcd.print("*");

  lcd.setCursor(0, 2);
  lcd.print("20    40    60    80");

  delay(2000);

  num++;

   }

   volume = lenght*width*height;

   Serial.println("Volume: ");
   Serial.println(volume);

   delay(10000);
             
} 

void left(){
  count_L++;
  }
void right(){
  count_R++;
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
