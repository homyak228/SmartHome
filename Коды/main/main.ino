#include <LiquidCrystal_I2C.h>
#include <iarduino_DHT.h>

#define BuzzerPin 11
#define LED_Red_pin 7
#define LED_White_pin 9
#define pinDHT 2
#define trigPin 6
#define echoPin 5

LiquidCrystal_I2C lcd(0x27, 20, 4);
iarduino_DHT dht(pinDHT);

int Fire = analogRead(A0);
int Gas = analogRead(A1);

void setup(){

  lcd.init();
  lcd.backlight();
  lcd.clear();

  Serial.begin(9600);

  pinMode(LED_White_pin, OUTPUT);
  pinMode(LED_Red_pin, OUTPUT);
  pinMode(4, INPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop(){
  int duration, cm; //Код для У.З. Сонара
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  cm = duration / 58;

  if (cm <= 15) {
    digitalWrite(LED_White_pin, HIGH);
    delay(4000);
  } else {
    digitalWrite(LED_White_pin, LOW);
  }
  
  delay(10);

  lcd.clear(); //Код для DHT датчика  
  lcd.setCursor(0,0);
  lcd.print("DHT:");
  lcd.setCursor(3,0);

  switch(dht.read()){
    case DHT_OK:             lcd.print((String) dht.hum + "% - " + dht.tem + "*C"); lcd.clear(); break;
    case DHT_ERROR_CHECKSUM: lcd.print("ERROR"); lcd.clear();                                    break;
    case DHT_ERROR_DATA:     lcd.print("ERROR"); lcd.clear();                                    break;
    case DHT_ERROR_NO_REPLY: lcd.print("ERROR"); lcd.clear();                                    break;
    default:                 lcd.print("ERROR"); lcd.clear();                                    break;
  } delay(10); 

  if (Fire) { //Код для датчика огня
    lcd.setCursor(0,0);
    lcd.print("Fire Alarm!!!");
    tone(BuzzerPin, 200);
    delay(10);
  }

  else {
    noTone(BuzzerPin);
    lcd.clear();
    delay(10);
  }
  if (Gas >= 10) { //Код для датчика газа
    digitalWrite(LED_Red_pin, HIGH);
    lcd.print("GAS LEAK!!!");
    tone(11, 200);
    delay(10);
    lcd.clear();
  }
  else {
    lcd.clear();
    noTone(11);
    digitalWrite(LED_White_pin, LOW);
    delay(10);
  }
  if (analogRead(A2) >= 10 and analogRead(A3) >= 10){ //Код для датчика протечки (Тест)
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Leak!");
    tone(BuzzerPin, 300);
    delay(10);
  }
  else {
    noTone(BuzzerPin);
    lcd.clear();
    delay(10);
  }  
}