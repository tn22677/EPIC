#include <PID_v1.h>
#include <Adafruit_MPU6050.h>


//defining pins
#define Left1 12
#define Left2 14
#define Right1 25
#define Right2 13

#define ENA 27 //right side
#define ENB 26 //left side

int motorPower = 10; //0 to 255

//PID variables
double Input, Output;
double desiredPitch = 0.0;
double Kp = 1;
double Ki = 0;
double Kd = 1;
PID errorCheck(&Input, &Output, &desiredPitch, Kp, Ki, Kd, P_ON_E, DIRECT);

Adafruit_MPU6050 mpu;

void setup() {
  // put your setup code here, to run once:
  // setting up pin modes
  Serial.begin(115200);

  pinMode(Left1, OUTPUT);
  pinMode(Right1, OUTPUT);
  pinMode(Left2, OUTPUT);
  pinMode(Right2, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  errorCheck.SetMode(AUTOMATIC);

  initMPU6050();

  Input = getTiltAngle();

}

void loop() {
  // put your main code here, to run repeatedly:

  // update the angle reading
  int angle = getTiltAngle();
  Input = angle;

  // calculate error
  errorCheck.Compute();
  Serial.print("Output = ");
  Serial.println(Output);

  // TODO: calculate motorPower
  motorPower = abs(Output);

  if(angle > 0 && angle < 60) {
    moveForward(motorPower); //speed from PID (temporary variable for speed)
  }
  else if(angle < 0 && angle > -60) {
    moveBackward(motorPower);
  }
  else{
    analogWrite(ENA, 0); 
    analogWrite(ENB, 0);
  }

}

void moveForward(int power) {
  //digitalWrite(pin, value)
  digitalWrite(Left1, HIGH);
  digitalWrite(Left2, LOW);
  digitalWrite(Right1, LOW);
  digitalWrite(Right2, HIGH);
  analogWrite(ENA, power); 
  analogWrite(ENB, power);
}


void moveBackward(int power) {
  digitalWrite(Left1, LOW);
  digitalWrite(Left2, HIGH);
  digitalWrite(Right1, HIGH);
  digitalWrite(Right2, LOW);
  analogWrite(ENA, power);
  analogWrite(ENB, power);
}

float getTiltAngle() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float position = a.acceleration.x - 0.5;
  float angle = (position / 10.0) * 90.0;

  // Optionally print debug info
  
  Serial.print("angle = ");
  Serial.println(angle);

  return angle;
}

void initMPU6050() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Adafruit MPU6050 test!");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) delay(10);
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

}