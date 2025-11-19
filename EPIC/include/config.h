#pragma once
#include <Arduino.h>

// Motor pins
#define Left1 12
#define Left2 14
#define Right1 25
#define Right2 13

#define ENA 27
#define ENB 26

// General variables
extern int motorPower;
extern double angle;
extern double PID;
extern double desired;

// Custom PID variables
extern double Kp;
extern double Ki;
extern double Kd;

extern int prevTime; 
extern int prevError;

extern double totalError; 
extern double error;