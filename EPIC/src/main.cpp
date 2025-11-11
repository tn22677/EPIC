#include <Arduino.h>
#include <PID_v1.h>         
#include "config.h"
#include "motor.h"
#include "imu.h"
#include "pid_custom.h"     // custom PID class


void setup() {
  Serial.begin(115200);

  motorInit();
  initMPU6050();

  //myPID.SetMode(AUTOMATIC);
  //Input = getTiltAngle();

  error = getError();
  angle = getTiltAngle();

  prevTime = 0;
  prevError = 0;
  totalError = 0;
}

void loop() {
  error = getError();

  PID = getProportionalError() + getIntegralError() + getDerivativeError();

  Serial.print("Output = ");
  Serial.println(Output);

  if (angle > 0 && angle < 75) {
    moveForward(motorPower);
  } else if (angle < 0 && angle > -75) {
    moveBackward(motorPower);
  } else {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }
}
