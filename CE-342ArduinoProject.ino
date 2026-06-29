#include <LiquidCrystal.h>

int aPin = 22;
int GND1 = 33;
int bPin = 23;
int GND2 = 34;
int cPin = 24;
int GND3 = 35;
int dPin = 25;
int GND4 = 36;
int ePin = 26;
int fPin = 27;
int gPin = 28;
int hPin = 29;
int pot = A8;
int buzzer = 5;
int ldr = A11;
int myLed = 6;
int led3 = 46;
long lastInterrupt = 0;
bool interrupted = false;
int temp, potValue, ldrValue;

LiquidCrystal lcd(36, 37, 26, 27, 28, 29);

#define LcdRWPin 35
#define BackLight 31

int tempsensor = A4;

void setup() {
  pinMode(led3, OUTPUT);
  pinMode(myLed, OUTPUT);
  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  pinMode(dPin, OUTPUT);
  pinMode(ePin, OUTPUT);
  pinMode(fPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(hPin, OUTPUT);
  pinMode(GND1, OUTPUT);
  pinMode(GND2, OUTPUT);
  pinMode(GND3, OUTPUT);
  pinMode(GND4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(LcdRWPin, OUTPUT);
  pinMode(BackLight, OUTPUT);

  Serial.begin(9600);
  attachInterrupt(1, myInterrupt, CHANGE);

  digitalWrite(BackLight, HIGH);
}

void loop() {
  if (millis() - lastInterrupt > 10000 && interrupted == true) {
    digitalWrite(led3, LOW);
    interrupted = false;
  }

  temp = (analogRead(tempsensor) * 5.0 * 100.0) / 1024.0;
  potValue = analogRead(pot);
  ldrValue = analogRead(ldr);

  if (temp < 20) {
    lcd.begin(16, 2);
    lcd.print("temp:");
    lcd.print(temp);
    lcd.print(" ldr:");
    lcd.print(ldrValue);

    lcd.setCursor(0, 1);
    lcd.print("pot: ");
    lcd.print(potValue);

    writeA();
    noTone(buzzer);
  } 
  else if (temp >= 20) {
    lcd.begin(16, 2);
    lcd.print("temp:");
    lcd.print(temp);
    lcd.print(" ldr:");
    lcd.print(ldrValue);

    lcd.setCursor(0, 1);
    lcd.print("pot: ");
    lcd.print(potValue);

    writeC();

    if (potValue > 600) {
      tone(buzzer, 1000);
    } 
    else if (potValue <= 600) {
      noTone(buzzer);
    }
  }

  if (ldrValue > 700) {
    digitalWrite(myLed, HIGH);
  } 
  else {
    digitalWrite(myLed, LOW);
  }

  Serial.println(ldrValue);

  delay(3000);
}

void writeA() {
  digitalWrite(GND1, HIGH);
  digitalWrite(GND2, LOW);
  digitalWrite(GND3, LOW);
  digitalWrite(dPin, LOW);
  digitalWrite(GND4, LOW);
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(fPin, HIGH);
  digitalWrite(ePin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(gPin, HIGH);
  digitalWrite(hPin, LOW);
}

void writeC() {
  digitalWrite(GND1, HIGH);
  digitalWrite(GND2, LOW);
  digitalWrite(GND3, LOW);
  digitalWrite(GND4, LOW);
  digitalWrite(dPin, HIGH);
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, LOW);
  digitalWrite(fPin, HIGH);
  digitalWrite(ePin, HIGH);
  digitalWrite(cPin, LOW);
  digitalWrite(gPin, LOW);
  digitalWrite(hPin, LOW);
}

void myInterrupt() {
  digitalWrite(led3, HIGH);
  interrupted = true;
  lastInterrupt = millis();
}