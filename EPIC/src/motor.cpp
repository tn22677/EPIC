#include "motor.h"
#include "config.h"

void motorInit(){
    
}

void moveForward(int power) {
  digitalWrite(Left1, HIGH);
  digitalWrite(Left2, LOW);
  digitalWrite(Right1, LOW);
  digitalWrite(Right2, HIGH);
  analogWrite(ENA, power); 
  analogWrite(ENB, power);
}

void moveBackward(int power) {
  digitalWrite(Left1, LOW);
  digitalWrite(Left2, HIGH);
  digitalWrite(Right1, HIGH);
  digitalWrite(Right2, LOW);
  analogWrite(ENA, power);
  analogWrite(ENB, power);
}
