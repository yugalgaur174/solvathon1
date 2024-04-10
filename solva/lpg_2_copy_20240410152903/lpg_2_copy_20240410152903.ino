#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED 2
#define Buzzer 7
#define Sensor A0

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  int value = analogRead(Sensor);
  Serial.println("LPG Value:");
  Serial.println(value);
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Value : ");
  lcd.print(value);
  lcd.print("  ");

  if (value > 400) {
    digitalWrite(LED, HIGH);
    digitalWrite(Buzzer, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("GAS Detected!");
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(Buzzer, LOW);
    lcd.setCursor(0, 1);
    lcd.print("             ");
  }
}