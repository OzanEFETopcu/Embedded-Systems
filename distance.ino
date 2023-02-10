#include "LIDARLite_v4LED.h"
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

LIDARLite_v4LED myLIDAR; 

void setup() {
  lcd.begin(20,4);
  Serial.begin(9600);
  Serial.println("Qwiic LIDARLite_v4 examples");
  Wire.begin(); 

  if (myLIDAR.begin() == false) {
    Serial.println("Device did not acknowledge! Freezing.");
    while(1);
  }
  Serial.println("LIDAR acknowledged!");
}

void loop() {
  float newDistance;


  newDistance = myLIDAR.getDistance();

  Serial.print("New distance: ");
  Serial.print(newDistance);
  Serial.println(" cm");

  delay(100); 

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


   
}
