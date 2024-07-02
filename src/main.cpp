#include <Arduino.h>

#define triggerPin 8
#define echoPin 9
#define buzzer 4
#define ledGreen 2
#define ledRed 3

long duration;
int distance;
int thresholdDistance = 196;

void setup()
{
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);
  digitalWrite(buzzer, LOW);

  Serial.begin(9600);
}

void sound(int speed, int freq)
{
  tone(buzzer, freq);
  delay(speed);
  noTone(buzzer);
}

void switchLED(int lampu)
{
  if (lampu == 1)
  {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzer, LOW);
  }
  else
  {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    sound(300, 2000);
  }
}

void loop()
{
  // membersihkan trigger sensor
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  // menjalankan trigger sensor
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Jarak: ");
  Serial.println(distance);

  if (distance > thresholdDistance) {
    switchLED(1);
  } else {
    switchLED(0);
  }
  delay(100);
}
