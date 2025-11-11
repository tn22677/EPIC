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
extern int angle;

// custom PID variables
extern double Kp = 1;
extern double Ki = 1;
extern double Kd = 1;

extern int prevTime; 
extern int prevError;

extern double totalError; //integral
extern double error;
