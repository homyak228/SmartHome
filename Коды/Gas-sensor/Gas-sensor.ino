#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

void setup(){
  lcd.init();
  lcd.clear();
  lcd.backlight();
  pinMode(A0, INPUT);
  pinMode(11, OUTPUT);
  pinMode(7, OUTPUT); 
}

void loop(){
  if(analogRead(A0) >= 100){
    digitalWrite(7, HIGH);
    lcd.print("GAS LEAK!!!");
    tone(11, 200);
    delay(100);
    lcd.clear();
  }
  else{
    lcd.clear();
    noTone(11);
    digitalWrite(7, LOW);
    delay(100);
  }
}