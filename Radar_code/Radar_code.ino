#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 10;
const int echoPin = 11;
const int led1 = 9;
const int led2 = 8;
const int buzzer = 5;
long duration;
int distance;
Servo myServo;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the LCD with I2C address 0x27

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
  myServo.attach(6);
  lcd.backlight();
  lcd.begin(16, 2); // Set LCD dimensions (16x2)
}

void loop() {
  lcd.clear(); // Clear the LCD at the start of each loop

  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
   delay(15);  
    distance = calculateDistance();

    if (distance < 10) {
      lcd.setCursor(0, 0);
      lcd.print("Obstacle Detected");
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(buzzer, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.print(" cm");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Angle: ");
      lcd.print(i);
      lcd.print(" deg");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("No Obstacle     ");
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(buzzer, LOW);
    }
    delay(40);
  }

  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(1);
    distance = calculateDistance();

    if (distance < 10) {
      lcd.setCursor(0, 0);
      lcd.print("Obstacle Detected");
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(buzzer, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.print(" cm");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Angle: ");
      lcd.print(i);
      lcd.print(" deg");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("No Obstacle    ");
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(buzzer, LOW);
    }
   delay(40);  
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}
