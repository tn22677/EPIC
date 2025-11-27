#include <Arduino.h>       
#include "config.h"
#include "motor.h"
#include "imu.h"
#include "pid_custom.h"   
#include <algorithm>
#include <cmath>

void setup() {
  Serial.begin(115200);

  motorInit();
  initMPU6050();

  //myPID.SetMode(AUTOMATIC);
  //Input = getTiltAngle();

  //testMotorSpeed();
  

  error = getError();
  angle = getTiltAngle();

  Serial.print(angle);

  prevTime = 0;
  prevError = 0;
  totalError = 0;
  PID = 0;

}

void loop() {
  error = getError();

  PID = getProportionalError() + getIntegralError() + getDerivativeError();
  // Serial.print("K = ");
  // Serial.println(getProportionalError());
  // Serial.print("I = ");
  // Serial.println(getIntegralError());
  // Serial.print("D = ");
  // Serial.println(getDerivativeError());


  // Serial.print("PID = ");
  // Serial.println(PID);

  //int motorSpeed = std::min(130.0, std::abs(PID));
  int motorSpeed = mapMotorSpeed(std::abs(PID));
  //int motorSpeed = std::abs(PID);

  Serial.print("angle = ");
  Serial.println(angle);

  Serial.print("Motor speed = ");
  Serial.println(motorSpeed);



  if (fabs(angle) > 75) {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }
  else if (error > 0) {
    moveForward(motorSpeed);
  } 
  else {
    moveBackward(motorSpeed);
  }
}
