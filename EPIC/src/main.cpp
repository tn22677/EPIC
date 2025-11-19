#include <Arduino.h>       
#include "config.h"
#include "motor.h"
#include "imu.h"
#include "pid_custom.h"   
#include <algorithm>
#include <cmath>

void setup() {
  Serial.begin(9600);

  motorInit();
  initMPU6050();

  //myPID.SetMode(AUTOMATIC);
  //Input = getTiltAngle();

  error = getError();
  angle = getTiltAngle();

  prevTime = 0;
  prevError = 0;
  totalError = 0;
  PID = 0;
}

void loop() {
  error = getError();
  angle = getTiltAngle();

  PID = getProportionalError() + getIntegralError() + getDerivativeError();

  Serial.print("PID = ");
  Serial.println(PID);

  //int motorSpeed = std::min(130.0, std::abs(PID));
  int motorSpeed = std::abs(PID);

  Serial.print("Motor speed = ");
  Serial.println(motorSpeed);

  if (angle > 0 && angle < 75) {
    moveBackward(motorSpeed);
  } else if (angle < 0 && angle > -75) {
    moveForward(motorSpeed);
  } else {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }
}
