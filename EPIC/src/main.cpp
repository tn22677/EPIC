#include <Arduino.h>
#include <PID_v1.h>         // optional\
#include "config.h"
#include "motor.h"
#include "imu.h"
#include "pid_custom.h"     // your custom PID class

// Global variable definitions
int motorPower = 10;
double Input, Output;
double desiredPitch = 0.0;
double Kp = 1, Ki = 0, Kd = 1;

// You can switch between library PID and your custom one
//PIDCustom myPID(Kp, Ki, Kd);
PID myPID(&Input, &Output, &desiredPitch, Kp, Ki, Kd, P_ON_E, DIRECT);

void setup() {
  Serial.begin(115200);

  pinMode(Left1, OUTPUT);
  pinMode(Right1, OUTPUT);
  pinMode(Left2, OUTPUT);
  pinMode(Right2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  initMPU6050();

  myPID.SetMode(AUTOMATIC);

  Input = getTiltAngle();
}

void loop() {
  double angle = getTiltAngle();
  myPID.Compute();

  motorPower = abs(Output);
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
