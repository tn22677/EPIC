#include "config.h"

// Allocate memory for all global variables
int motorPower = 0;
double angle = 0;
double PID = 0;

double Kp = 1;
double Ki = 1;
double Kd = 1;

int prevTime = 0;
int prevError = 0;

double totalError = 0;
double error = 0;