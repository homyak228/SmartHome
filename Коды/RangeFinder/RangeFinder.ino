#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int trigPin = 11;
int echoPin = 12;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  int duration, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  cm = duration / 58;

  lcd.setCursor(0,0);
  lcd.print(cm);
  lcd.setCursor(3,0);
  lcd.print("cm");
  
  delay(100);

  lcd.clear();
}