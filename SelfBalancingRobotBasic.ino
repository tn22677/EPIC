#include <PID_v1.h>

//defining pins
#define Left1 12
#define Left2 13
#define Right1 14
#define Right2 15

#define ENA 16 //right side //enable A
#define ENB 17 //left side  // enable B

#define PIN_INPUT 0 //TODO change values for pins (sensor pins)
#define PIN_OUTPUT 3

int motorPower = 10; //0 to 255

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


void setup() {
  // put your setup code here, to run once:
  // setting up pin modes
  pinMode(Left1, OUTPUT);
  pinMode(Right1, OUTPUT);
  pinMode(Left2, OUTPUT);
  pinMode(Right2, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  //initialize the variables we're linked to
  Input = analogRead(PIN_INPUT);
  Setpoint = 100;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop() {
  // put your main code here, to run repeatedly:


  // int angle = getTiltAngle();
  // if(angle > 0 && angle < 60) {
  //   moveForward(motorPower); //speed from PID (temporary variable for speed)
  // }
  // else if(angle < 0 && angle < -60) {
  //   moveBackward(motorPower);
  // }

  //PID
  Input = analogRead(PIN_INPUT);
  myPID.Compute();
  analogWrite(PIN_OUTPUT, Output);
  
}

void moveForward(int power) {
  //digitalWrite(pin, value)
  digitalWrite(Left1, HIGH);
  digitalWrite(Left2, LOW);
  digitalWrite(Right1, HIGH);
  digitalWrite(Right2, LOW);
  analogWrite(ENA, power); 
  analogWrite(ENB, power);
}


void moveBackward(int power) {
  digitalWrite(Left1, LOW);
  digitalWrite(Left2, HIGH);
  digitalWrite(Right1, LOW);
  digitalWrite(Right2, HIGH);
  analogWrite(ENA, power);
  analogWrite(ENB, power);
}

int getTiltAngle() {
  //get angle from gyroscope
}

float getPIDTuning() {

}
