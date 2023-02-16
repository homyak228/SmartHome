#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int Fire = digitalRead(4);
int BuzzerPin = 11;
int Buzzer = digitalRead(BuzzerPin);

void setup(){
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(4, INPUT);
  Serial.begin(9600);
}

void loop(){
  if (Fire) {
    lcd.setCursor(0,0);
    lcd.print("Fire Alarm!!!");
    tone(BuzzerPin, 200);
    delay(100);
  }
  else {
    noTone(BuzzerPin);
    lcd.clear();
    delay(100);
  }
}
