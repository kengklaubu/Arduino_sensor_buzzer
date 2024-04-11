#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define NOTE_C4  261.63
#define NOTE_D4  293.66
#define NOTE_E4  329.63
#define NOTE_F4  349.23
#define NOTE_G4  392.00
#define NOTE_A4  440.00
#define NOTE_B4  493.88
#define NOTE_C5  523.25

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13; //led pin
const int ledPin1 = 3; //yellow color
const int ledPin2 = 4; //green color

// defines variables
long duration;
int distance;
int safetyDistance;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT); //RED
  pinMode(ledPin1, OUTPUT); //YELLOW
  pinMode(ledPin2, OUTPUT); //GREEN
  
  Serial.begin(9600); 
  
  lcd.init();
  // Turn on the backlight
  lcd.backlight();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  safetyDistance = distance;
  if (safetyDistance <= 10) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH);
    tone(buzzer, NOTE_C5); 
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  } 
  else if (safetyDistance <= 20) {
    digitalWrite(ledPin1, HIGH);
    tone(buzzer, NOTE_C5);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin, LOW);
  } 
  else if (safetyDistance <= 30) {
    digitalWrite(ledPin2, HIGH);
    tone(buzzer, NOTE_C5);
  } 
  else {
    noTone(buzzer);
    digitalWrite(buzzer, LOW);
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  }

  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm     ");
  
  Serial.print("Distance: ");
  Serial.println(distance);
}
