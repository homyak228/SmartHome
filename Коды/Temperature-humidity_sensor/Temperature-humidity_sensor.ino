#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>

int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
void loop() {
  byte temperature;
  byte humidity;

  lcd.setCursor(0,0);
  lcd.print((int)temperature);
  lcd.setCursor(2,0);
  lcd.print("°C");
  lcd.setCursor(0,1);
  lcd.print((int)humidity);
  lcd.setCursor(2,1);
  lcd.print("%");
  delay(500);
}
