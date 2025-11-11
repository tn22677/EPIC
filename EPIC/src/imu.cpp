#include "imu.h"
#include "config.h"
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;

void initMPU6050() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Initializing MPU6050...");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip!");
    while (1) delay(10);
  }

  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

float getTiltAngle() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float position = a.acceleration.x - 0.5;
  float angle = (position / 10.0) * 90.0;

  Serial.print("angle = ");
  Serial.println(angle);

  return angle;
}
