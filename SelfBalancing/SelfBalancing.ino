#include <PID_v1.h>

//defining pins
#define Left1 12
#define Left2 13
#define Right1 14
#define Right2 15

#define ENA 16 //right side
#define ENB 17 //left side

int motorPower = 10; //0 to 255
long previousTime = 0;
long time = 0;

//PID variables
double Input, Output;
const double desiredPitch = 0.0;
double Kp = 1;
double Ki = 1;
double Kd = 1;
PID errorCheck(&Input, &Output, &desiredPitch, Kp, Ki, Kd, P_ON_E, DIRECT);


void setup() {
  // put your setup code here, to run once:
  // setting up pin modes
  pinMode(Left1, OUTPUT);
  pinMode(Right1, OUTPUT);
  pinMode(Left2, OUTPUT);
  pinMode(Right2, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  previousTime = millis();

  errorCheck.SetMode(AUTOMATIC);
  // TODO: get first input for input
}

void loop() {
  // put your main code here, to run repeatedly:

  // update the angle reading
  int angle = getTiltAngle();
  Input = angle;

  // calculate error
  myPid.Compute();

  // calculate motorPower
  

  if(angle > 0 && angle < 60) {
    moveForward(motorPower); //speed from PID (temporary variable for speed)
    previousTime = millis();
  }
  else if(angle < 0 && angle < -60) {
    moveBackward(motorPower);
    previousTime = millis();
  }

}

void moveForward(int power) {
  //digitalWrite(pin, value)
  digitalWrite(Left1, HIGH);
  digitalWrite(Left2, LOW);
  digitalWrite(Right1, HIGH);
  digitalWrite(Right2, LOW);
  analogWrite(ENA, power); 
  analogWrite(EBA, power);
}


void moveBackward(int power) {
  digitalWrite(Left1, LOW);
  digitalWrite(Left2, HIGH);
  digitalWrite(Right1, LOW);
  digitalWrite(Right2, HIGH);
  analogWrite(ENA, power);
  analogWrite(EBA, power);
}

int getTiltAngle() {
  //get angle from gyroscope
}

float getPIDTuning() {

}