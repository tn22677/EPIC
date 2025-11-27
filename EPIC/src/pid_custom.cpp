#include "imu.h"
#include "config.h"

double getError(){
    double angle = getTiltAngle();
    double error = desired - angle;

    return error;
}

double getProportionalError(){
    return error*Kp;
}

double getDerivativeError(){
    int currTime = millis();
    double timeChange = ((double) (currTime - prevTime)) / 1000.0;

    double dErr = (error - prevError)/(timeChange);

    prevTime = currTime;
    prevError = error;

    return Kd*dErr;
}

double getIntegralError(){
    if (abs(error) < 1){
        totalError = 0;
    }
    else{
        totalError += error;
    }

    return Ki*totalError;
}

