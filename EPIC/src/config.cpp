#include "config.h"

// Allocate memory for all global variables
int motorPower = 0;
double angle = 0;
double PID = 0;
double desired = -3.12;

double Kp = 5;
double Ki = 0;
double Kd = 0;

int prevTime = 0;
int prevError = 0;

double totalError = 0;
double error = 0;