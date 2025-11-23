#pragma once
#include <Arduino.h>

void motorInit();
void moveForward(int power);
void moveBackward(int power);
double mapMotorSpeed(double spdIn);
void testMotorSpeed();