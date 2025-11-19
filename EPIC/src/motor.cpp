#include "motor.h"
#include "config.h"

void motorInit(){
  pinMode(Left1, OUTPUT);
  pinMode(Right1, OUTPUT);
  pinMode(Left2, OUTPUT);
  pinMode(Right2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void moveForward(int power) {
  digitalWrite(Left1, HIGH);
  digitalWrite(Left2, LOW);
  digitalWrite(Right1, HIGH);
  digitalWrite(Right2, LOW);
  analogWrite(ENA, power); 
  analogWrite(ENB, power);
}

void moveBackward(int power) {
  digitalWrite(Left1, LOW);
  digitalWrite(Left2, HIGH);
  digitalWrite(Right1, LOW);
  digitalWrite(Right2, HIGH);
  analogWrite(ENA, power);
  analogWrite(ENB, power);
}

double mapMotorSpeed(double x) {
    // cap input first
    if (x < 0) x = 0;
    if (x > 255) x = 255;

    // hard-coded linear mapping from [0,255] → [50,255]
    int out = (x * (255 - 40) / 255) + 40;

    if (out < 40) out = 40;
    if (out > 255) out = 255;
    return out;
}