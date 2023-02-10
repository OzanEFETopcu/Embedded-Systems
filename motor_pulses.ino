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

      
      lcd.begin(16, 2);
      Serial.begin(9600);
      attachInterrupt(digitalPinToInterrupt(btn3),left, RISING);
      attachInterrupt(digitalPinToInterrupt(btn4),right, RISING);
      Wire.begin();
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
void loop()   
{  
            
 xMap = 0;
 xValue = analogRead(A8);
 yValue = analogRead(A9);

 xMap =(xValue)*19/1023;

 getBearing();



 if (Serial.available() > 0){
  
    String message = Serial.readStringUntil('\n'); 
    Serial.print("Message received, content: ");  
    Serial.println(message);
    
    int pos_s = message.indexOf("Move");
    int pos_s2 = message.indexOf("Turn");
    Serial.println(pos_s2);

    if (pos_s > -1){
      Serial.println("Command = Move ");
      pos_s = message.indexOf(":");

      if (pos_s > -1){
        String stat = message.substring(pos_s + 1);
        lcd.print(stat);

        distval = stat.toInt();
        Serial.print("Distance: ");
        Serial.println(distval);
        Serial.println("I am here, queen!!!");

        if (distval > 0) {
          digitalWrite(Motor_L_dir_pin, Motor_forward);
          digitalWrite(Motor_R_dir_pin, Motor_forward);
        }
        if (distval < 0) {
          digitalWrite(Motor_L_dir_pin, Motor_return);
          digitalWrite(Motor_R_dir_pin, Motor_return);
          distval = -(1)*distval;
        }

        
        
        while (count_L*DistancePerPulse < distval) {

          analogWrite(Motor_L_pwm_pin, 254);
          analogWrite(Motor_R_pwm_pin, 254);
          Serial.print(count_L);
          
          }

          analogWrite(Motor_L_pwm_pin, 0);
          analogWrite(Motor_R_pwm_pin, 0);

          delay(500);

          x = 0;
          count_L = 0;
        
      }  
    }
    else{
     Serial.println("No greeting found, try typing Print:Hi or Print:Hello\n");
    }


    if (pos_s2 > -1){
      Serial.println("Command = Turn ");
      pos_s2 = message.indexOf(":");

      if (pos_s2 > -1 || pos_s2 < -1){
        String stat = message.substring(pos_s2 + 1);
        lcd.print(stat);

        distval = stat.toInt();
        Serial.print("Distance: ");
        Serial.println(distval);
        Serial.println("I am here, queen!!!");

        int loc;

        loc = bearing + distval;

        digitalWrite(Motor_R_dir_pin,Motor_forward);  
        digitalWrite(Motor_L_dir_pin,Motor_forward);


        if (loc <= 360 && loc >= 0){
           do {
            Serial.print("Bearing: ");
            Serial.print(bearing);
            Serial.print ("\n");
            Serial.print("Loc: ");
            Serial.print(loc);
              if (distval > 0){
                analogWrite(Motor_L_pwm_pin,0);
                analogWrite(Motor_R_pwm_pin, 50);
              }else {
                analogWrite(Motor_L_pwm_pin,50);
                analogWrite(Motor_R_pwm_pin, 0);
              }   
              getBearing();
            }while (loc != bearing);
          } else if (loc > 360) {
            loc = loc - 360;
            do {
            Serial.print("Bearing: ");
            Serial.print(bearing);
            Serial.print ("\n");
            Serial.print("Loc: ");
            Serial.print(loc);
              if (distval > 0){
                analogWrite(Motor_L_pwm_pin,0);
                analogWrite(Motor_R_pwm_pin, 50);
              }else {
                analogWrite(Motor_L_pwm_pin,50);
                analogWrite(Motor_R_pwm_pin, 0);
              }
              getBearing();     
            }while (loc != bearing);
           } else if ( loc < 0 ){
            loc = loc + 360;
            do {
            Serial.print("Bearing: ");
            Serial.print(bearing);
            Serial.print ("\n");
            Serial.print("Loc: ");
            Serial.print(loc);
              if (distval > 0){
                analogWrite(Motor_L_pwm_pin,0);
                analogWrite(Motor_R_pwm_pin, 50);
              }else {
                analogWrite(Motor_L_pwm_pin,50);
                analogWrite(Motor_R_pwm_pin, 0);
              }
              getBearing();     
            }while (loc != bearing);
            }

         analogWrite(Motor_L_pwm_pin,0);
         analogWrite(Motor_R_pwm_pin, 0);

        
      }  
    }
  }
 

       
      

      

      /*Serial.print(motor_L);
      Serial.print(" ");
      Serial.print(motor_R);
      Serial.print(" ");
      Serial.print(xValue);
      Serial.print(" ");
      Serial.print(yValue);
      Serial.print(" ");
       Serial.print(" ");
      Serial.print(voltage5_1);
      Serial.print(" ");
      Serial.print(ratio);
      Serial.print(" ");
      Serial.print("\n");

      delay(1000);

      Serial.print(left_count);
      Serial.print(" ");
      Serial.print(right_count);
      Serial.print("\n");

      distance = left_count/6.85;
      distance_str = String(distance);

      lcd.setCursor(1,1);
      lcd.print(distance_str + "cm:s");
      */
                 
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
