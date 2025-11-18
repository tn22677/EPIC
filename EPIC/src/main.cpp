#include <Arduino.h>       
#include "config.h"
#include "motor.h"
#include "imu.h"
#include "pid_custom.h"   


void setup() {
  Serial.begin(115200);

  motorInit();
  initMPU6050();

  //myPID.SetMode(AUTOMATIC);
  //Input = getTiltAngle();

  error = getError();
  angle = getTiltAngle();

  Kp = 1;
  Ki = 1;
  Kd = 1;

  prevTime = 0;
  prevError = 0;
  totalError = 0;
  PID = 0;
}

void loop() {
  error = getError();
  angle = getTiltAngle();

  PID = getProportionalError() + getIntegralError() + getDerivativeError();

  Serial.print("Output = ");
  Serial.println(PID);


  if (angle > 0 && angle < 75) {
    moveForward(PID);
  } else if (angle < 0 && angle > -75) {
    moveBackward(PID);
  } else {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }
}
