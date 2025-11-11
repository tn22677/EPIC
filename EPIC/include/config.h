#pragma once
#include <Arduino.h>

// Motor pins
#define Left1 12
#define Left2 14
#define Right1 25
#define Right2 13

#define ENA 27 // Right side
#define ENB 26 // Left side

// Motor variables
extern int motorPower;

// PID variables
extern double Input, Output, desiredPitch;
extern double Kp, Ki, Kd;