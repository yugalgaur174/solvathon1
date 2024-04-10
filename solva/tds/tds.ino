#include <EEPROM.h>
#include "GravityTDS.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 

#define TdsSensorPin A1
 

GravityTDS gravityTds;
 

 
float tdsValue = 0;
float temp = 25.0;
 
void setup()
{
    Serial.begin(115200);
    lcd.begin(16,2);
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
}
 
void loop()
{
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    Serial.print("Temperature is: "); 
    Serial.print(temp);
    
    lcd.setCursor(0, 0);
    lcd.print("TDS: ");
    lcd.print(tdsValue,0);
    lcd.print(" PPM");
 
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print(" C");
    
    delay(1500);
    lcd.clear();
}